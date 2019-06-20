// Express
const express = require('express')
const app = express()

// Server static file from public directory
app.use( express.static('public') )

// Start Server
app.listen( 2222, () => console.log('Server running on port 2222') )
