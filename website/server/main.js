express = require('express');

const app = express();

const toFENstring = chessPosition => {
    fenString = '';
    for (let i = 0; i < 8; i++) {
        for (let j = 0; j < 8; j++) {
            fenString += chessPosition[i*8 + j];
        }
        fenString += '/';
    } 
    console.log(fenString);
    fenString = fenString.replace(/\-\-\-\-\-\-\-\-/g, "8");
    fenString = fenString.replace(/\-\-\-\-\-\-\-/g, "7");
    fenString = fenString.replace(/\-\-\-\-\-\-/g, "6");
    fenString = fenString.replace(/\-\-\-\-\-/g, "5");
    fenString = fenString.replace(/\-\-\-\-/g, "4");
    fenString = fenString.replace(/\-\-\-/g, "3");
    fenString = fenString.replace(/\-\-/g, "2");
    fenString = fenString.replace(/\-/g, "1");
    return fenString
}

app.get("/api/:chessPosition", (req, res) =>  {
    let chessPosition = req.params.chessPosition;
    let fenString = toFENstring(chessPosition);
    fenString = `${fenString} b KQkq - 0 1`;
    console.log(fenString);
    const spawn = require('child_process').spawn;
    const proc = spawn('../../main.exe', fenString.split(' '));

    let output = '';
    proc.stdout.on('data', (chunk) => {
        console.log(chunk.toString());
        output += chunk.toString();
    });
    proc.on('exit', () => {
      res.send(output.split('-').map(c => [Math.floor(c/8), c%8]));
    });
})

app.get("*", (req, res) => {
    let path = req.path;
    console.log(path);
    let filePath =  __dirname.split("\\").slice(0, __dirname.split("\\").length-1).join("/") + "/client/" + path;
    res.sendFile(filePath);
})

app.listen(3000, () =>
  console.log('Example app listening on port 3000!'),
);