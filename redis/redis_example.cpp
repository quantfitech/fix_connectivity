#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/select.h>
#include <hiredis/hiredis.h>
#include <hiredis/async.h>
//#include <hiredis/adapters/libevent.h>

// Global variables for Redis connections
redisContext *publish_context;
redisContext *subscribe_context;

// Signal handler for graceful shutdown
void signal_handler(int sig) {
    printf("Caught signal %d, cleaning up and exiting...\n", sig);
    if (publish_context) redisFree(publish_context);
    if (subscribe_context) redisFree(subscribe_context);
    exit(0);
}

// Function to publish a message to a Redis channel
void publish_message(const char *channel, const char *message) {
    redisReply *reply = static_cast<redisReply*>(redisCommand(publish_context, "PUBLISH %s %s", channel, message));
    if (!reply) {
        fprintf(stderr, "Publish failed: %s\n", publish_context->errstr);
        return;
    }
    freeReplyObject(reply);
}

// Function to handle incoming messages from subscribed channels
void handle_message(redisReply *reply) {
    if (reply->type == REDIS_REPLY_ARRAY && reply->elements == 3) {
        if (strcmp(reply->element[0]->str, "message") == 0) {
            printf("Received message from channel %s: %s\n",
                   reply->element[1]->str, reply->element[2]->str);
        }
    }
}

int main() {
    // Set up signal handling
    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);

    // Connect to Redis
    const char *redis_host = "127.0.0.1";
    int redis_port = 6379;
    struct timeval timeout = {1, 500000}; // 1.5 seconds

    publish_context = redisConnectWithTimeout(redis_host, redis_port, timeout);
    if (publish_context == NULL || publish_context->err) {
        if (publish_context) {
            fprintf(stderr, "Publish connection error: %s\n", publish_context->errstr);
            redisFree(publish_context);
        } else {
            fprintf(stderr, "Publish connection error: can't allocate redis context\n");
        }
        exit(1);
    }

    subscribe_context = redisConnectWithTimeout(redis_host, redis_port, timeout);
    if (subscribe_context == NULL || subscribe_context->err) {
        if (subscribe_context) {
            fprintf(stderr, "Subscribe connection error: %s\n", subscribe_context->errstr);
            redisFree(subscribe_context);
        } else {
            fprintf(stderr, "Subscribe connection error: can't allocate redis context\n");
        }
        redisFree(publish_context);
        exit(1);
    }

    // Subscribe to channels
    const char *channels[] = {"channel1", "channel2"};
    for (int i = 0; i < sizeof(channels) / sizeof(channels[0]); i++) {
        redisReply *reply = static_cast<redisReply*>(redisCommand(subscribe_context, "SUBSCRIBE %s", channels[i]));
        if (!reply) {
            fprintf(stderr, "Subscribe failed: %s\n", subscribe_context->errstr);
            redisFree(publish_context);
            redisFree(subscribe_context);
            exit(1);
        }
        freeReplyObject(reply);
    }

    // Main loop using select()
    while (1) {
        fd_set fds;
        FD_ZERO(&fds);
        FD_SET(subscribe_context->fd, &fds);

        // Wait for activity on the subscription connection
        int ret = select(subscribe_context->fd + 1, &fds, NULL, NULL, NULL);
        if (ret < 0) {
            perror("select() failed");
            break;
        }

        if (FD_ISSET(subscribe_context->fd, &fds)) {
            redisReply *reply;
            if (redisGetReply(subscribe_context, (void **)&reply) == REDIS_OK) {
                handle_message(reply);
                freeReplyObject(reply);
            } else {
                fprintf(stderr, "Failed to read reply: %s\n", subscribe_context->errstr);
                break;
            }
        }
    }

    // Cleanup
    redisFree(publish_context);
    redisFree(subscribe_context);
    return 0;
}