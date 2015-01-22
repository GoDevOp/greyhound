// ****************************************************************************
// ********************* WARNING * WARNING * WARNING **************************
// ****************************************************************************
//
// DO NOT COMMIT WITH REAL CREDENTIALS.
// THIS FILE SHOULD ONLY BE POPULATED ON A SECURE DEPLOYMENT.
//
// For deployment use, copy this file to "credentials.js" and supply real
// values for the strings below.

var credentials = {
    aws: {
        // Base URL to access the specified bucket (may specify a region).
        url:    's3.amazonaws.com',

        // Base bucket name to put/read serialized pointcloud data.
        bucket: 'my-bucket-name-goes-here',

        // Credentials for the above specified URL/bucket.
        access: 'AwsAccessKeyId-goes-here',
        hidden: 'AwsHiddenAccessKey-goes-here'
    }
};

module.exports = credentials;

