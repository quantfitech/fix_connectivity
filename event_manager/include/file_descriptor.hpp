#ifndef FILE_DESCRIPTOR_HPP
#define FILE_DESCRIPTOR_HPP


namespace qfapp {

    class FileDescriptor {
    public:
        virtual ~FileDescriptor() = default;

        // Callbacks
        virtual int onData() = 0;    // Called when data is available
        virtual void onError() = 0;  // Called on errors
        virtual void onClose() = 0;  // Called on close
        virtual int onWrite() = 0;   // Called when writable

        virtual void onConnected() = 0;   // Called when connected

        // Get the associated file descriptor
        virtual int getFd() const = 0;
        virtual bool isInitiator() const = 0;

        virtual bool isConnected() const = 0;

    };
}

#endif // FILE_DESCRIPTOR_HPP