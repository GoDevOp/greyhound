#pragma once

#include <string>
#include <vector>

#include "curl.hpp"

class PutCollector;
class GetCollector;

struct S3Info
{
    S3Info(
            std::string baseAwsUrl,
            std::string bucketName,
            std::string awsAccessKeyId,
            std::string awsSecretAccessKey)
        : exists(true)
        , baseAwsUrl(baseAwsUrl)
        , bucketName(bucketName)
        , awsAccessKeyId(awsAccessKeyId)
        , awsSecretAccessKey(awsSecretAccessKey)
    { }

    S3Info()
        : exists(false)
        , baseAwsUrl()
        , bucketName()
        , awsAccessKeyId()
        , awsSecretAccessKey()
    { }

    const bool exists;
    const std::string baseAwsUrl;
    const std::string bucketName;
    const std::string awsAccessKeyId;
    const std::string awsSecretAccessKey;
};

class S3
{
public:
    S3(
            std::string awsAccessKeyId,
            std::string awsSecretAccessKey,
            std::string baseAwsUrl = "s3.amazonaws.com",
            std::string bucketName = "");

    ~S3();

    // Functions that take a Collector argument asynchonously push their
    // results into the collector, so they will return immediately.
    //
    // IMPORTANT: It is the responsibility of the caller to limit these calls
    // so that they do not get too far ahead of the CurlBatch batchSize, in
    // which case many threads will be spawned and be blocked until the
    // CurlBatch can acquire an entry.
    //
    // IMPORTANT: Curl's timeout parameter must be set, as threads spawned
    // by the asynchronous calls here cannot return until the Curl call
    // completes.

    HttpResponse get(std::string file);
    void get(uint64_t id, std::string file, GetCollector* collector);

    HttpResponse put(std::string file, const std::vector<uint8_t>* data);
    HttpResponse put(std::string file, const std::string& data);
    void put(
            uint64_t id,
            std::string file,
            const std::vector<uint8_t>* data,
            PutCollector* collector);

    const std::string& baseAwsUrl() const { return m_baseAwsUrl; }
    const std::string& bucketName() const { return m_bucketName; }

    std::vector<std::string> getHeaders(std::string filePath) const;
    std::vector<std::string> putHeaders(std::string filePath) const;

private:
    std::string getHttpDate() const;

    std::string getSignedEncodedString(
            std::string command,
            std::string file,
            std::string httpDate,
            std::string contentType = "") const;

    std::string getStringToSign(
            std::string command,
            std::string file,
            std::string httpDate,
            std::string contentType) const;

    std::vector<uint8_t> signString(std::string input) const;
    std::string encodeBase64(std::vector<uint8_t> input) const;
    std::string prefixSlash(const std::string& in) const;

    const std::string m_awsAccessKeyId;
    const std::string m_awsSecretAccessKey;
    const std::string m_baseAwsUrl;
    const std::string m_bucketName;

    std::shared_ptr<CurlBatch> m_curlBatch;
};

