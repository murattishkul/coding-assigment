var express = require('express')
var fs = require('fs')
var request = require ('request')
var cheerio = require ('cheerio')
var csv = require('fast-csv')
var ws = fs.createWriteStream('my.csv') 

app = express();

app.get('/', function(req, res){
    var url = 'http://www.philfoodex.org.ph/Members.php';

    request(url, function(err, response, doc){
    if(!err){
          var $ = cheerio.load(doc);
          var crawl = []; var ans = [];
          $('tr').each(function(index, value){
        var data = $(this);
        if(index !==0 && index !==1){
            let name = data.children().first().children().first().text();
            let prodList = data.children().first().children().last().text();
            let siteURL = data.children().last().children().first().children().first().text();
            if(name !== "") crawl.push(name);
            if(prodList !== "") crawl.push(prodList);
            if(siteURL !== "") crawl.push(siteURL) ; else crawl.push('URL is not available');
            ans.push(crawl);
            crawl = [];
            }
        })
    }      
    csv
        .write(
            ans, {headers : true}
        ).pipe(ws);

    console.log('Done Crawling... checkout the my.csv file')
    res.send('Done Crawling...')
    });
})

app.listen(8000);

console.log('Crawling Server listens to port 8000');

exports = module.exports = app;