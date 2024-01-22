# 使用minio-cpp踩过的那些坑

1. 去vcpkg化: 去除vcpkg，将minio编译为静态库. 
    简单来说，就是拷贝使用到的vcpkg的include和lib文件夹，然后修改了顶部CMakeLists.txt
2. 调用GetPresignedObjectUrl遇到的两个问题
    - connect to 127.0.0.1 port 9000 failed: Connection refused。

        将`127.0.0.1`修改为具体的本机ip地址

    - 访问`GetPresignedObjectUrl`获得的url，出现报错: SignatureDoesNotMatch.

        这是由于minio-cpp在计算预签名时没有加入`port`导致的，需要修改`signer::PresignV4`函数:

        ```cpp
        minio::utils::Multimap& minio::signer::PresignV4(
            http::Method method, std::string& host, int port, std::string& uri,
            std::string& region, utils::Multimap& query_params, std::string& access_key,
            std::string& secret_key, utils::Time& date, unsigned int expires) {
            std::string service_name = "s3";
            std::string scope = GetScope(date, region, service_name);
            std::string canonical_headers = "host:" + host + ":" + std::to_string(port);
            std::string signed_headers = "host";
            ...
        }
        ```