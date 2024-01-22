// MinIO C++ Library for Amazon S3 Compatible Cloud Storage
// Copyright 2022 MinIO, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "miniocpp/client.h"

int main(int argc, char* argv[]) {
  std::string host = "http://192.168.0.106:9000";
  // std::string host = "http://127.0.0.1:9000"; // error:connect to 127.0.0.1 port 9000 failed: Connection refused
  minio::http::Url url = minio::http::Url::Parse(host);

  std::cout << "url: " << host << ", port: " << url.port << ", host: " << url.host << std::endl;

  // Create S3 base URL.
  minio::s3::BaseUrl base_url(host, false);

  // Create credential provider.
  minio::creds::StaticProvider provider(
      "AiEj4haD2O0KwVOsqPcA", "b8QLLjv1MxcyRfzlv5bbVQgo3vMblvrhq42bRjrw");

  // Create S3 client.
  minio::s3::Client client(base_url, &provider);

  // Create make bucket arguments.
  minio::s3::MakeBucketArgs args;
  args.bucket = "xxx";

  // Call make bucket.
  minio::s3::MakeBucketResponse resp = client.MakeBucket(args);

  // Handle response.
  if (resp) {
    std::cout << "my-bucket is created successfully" << std::endl;
  } else {
    std::cout << "unable to create bucket; " << resp.Error().String()
              << std::endl;
  }

  return 0;
}
