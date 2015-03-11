var mysql      = require('mysql');
var connection = mysql.createConnection({
  host     : 'localhost',
  user     : 'us',
  password : 'controller',
  database : 'iws_week4'
});
//Setup express, body-parser and app
var express    = require('express');
var app        = express();  
var bodyParser = require('body-parser');

// configure app to use bodyParser()
// this will let us get the data from a POST
app.use(bodyParser.urlencoded({ extended: true }));
app.use(bodyParser.json());

//Use defined port or use 8080 (PORT=1234 node script.js OR export PORT=1234 THEN node app.js)
var port = process.env.PORT || 8080;        

var router = express.Router(); 

connection.connect();

//Here we define our API functions
router.get('/', function(req, res) {
    res.json({ message: 'ONLINE' });   
});

router.route('/data').post(function(req, res) {
    var post= req.body;
    
    console.log('HTTP header data: ' + JSON.stringify(req.headers));
    console.log('HTTP body data: ' + JSON.stringify(req.body));
	connection.query('INSERT INTO measurements SET ?', post, function(error){
	    if(error){
	      console.log(error.message);
	      res.json({ DBresult: 'insert failure' });
	    }else{
	      console.log('succes');
	      res.json({ DBresult: 'insert success' });
	    }
  	});
	
});


//Set the path for our API
app.use('/iws', router);

//Heartbea
app.listen(port);
console.log('Script started on ' + port);



//connection.connect();
//
//connection.query('SELECT * from meetwaarde', function(err, rows, fields) {
//  if (!err)
//    console.log('The solution is: ', rows);
//  else
//    console.log('Error while performing Query.');
//});
//connection.end();
