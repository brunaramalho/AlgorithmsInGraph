# AlgorithmsInGraph
To study basic concepts in graphs and structural tools, with emphasis in hierarchies of chordal and interval graphs.

## Setup

Run `npm install` on the folder to install the dependencies.

## Run the server

Run `node .` to put the server up.

## API

Make a POST request to `localhost:3000/static` with json containing a key `args` with the arguments to be passed to the program:
```json
{
  "args": "4"
}
```

Example: `curl -X POST -d '{"args": "4"}' -H "Content-Type: application/json" localhost:3000/static`
