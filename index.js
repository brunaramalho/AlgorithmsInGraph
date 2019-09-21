const { exec, execSync } = require('child_process');
const express = require('express');
const app = express();

app.use(express.json());

var allowCrossDomain = function(req, res, next) {
  res.header('Access-Control-Allow-Origin', "*");
  res.header('Access-Control-Allow-Methods', 'GET,PUT,POST,DELETE');
  res.header('Access-Control-Allow-Headers', 'Content-Type');
  next();
}
app.use(allowCrossDomain); 

app.post('/dynamic', (req, res) => {
  console.log(req.body);
  let command = './dynamic ' + req.body.args;
  console.log(command);
  exec(command, (error, stdout, stderr) => {
    res.json({ output: stdout });
  });
});

app.post('/static', (req, res) => {
  console.log(req.body);
  let command = './static ' + req.body.args;
  console.log(command);
  exec(command, (error, stdout, stderr) => {
    res.json({ output: stdout });
  });
});

app.post('/chordal', (req, res) => {
  console.log(req.body);
  let command = './reconhecimentoCordal ' + req.body.args;
  console.log(command);
  exec(command, (error, stdout, stderr) => {
    res.json({ output: stdout });
  });
});

app.post('/block', (req, res) => {
  console.log(req.body);
  let command = './reconhecimentoBloco ' + req.body.args;
  console.log(command);
  exec(command, (error, stdout, stderr) => {
    res.json({ output: stdout });
  });
});

app.listen(3000, () => {
  execSync('gcc static.c -o static');
  execSync('g++ dynamicBlock.cpp -o dynamic');
  execSync('gcc reconhecimentoBloco.c -o reconhecimentoBloco');
  execSync('gcc reconhecimentoCordal.c -o reconhecimentoCordal');
  console.log('Listening on port 3000');
});
