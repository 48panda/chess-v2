function tableToArray(table) {
    var array = [];
    for (let i = 0; i < table.querySelectorAll("tr").length; i++) {
        array[i] = [];
        for (let j = 0; j < table.querySelectorAll("tr")[i].querySelectorAll("td").length; j++) {
            array[i][j] = table.querySelectorAll("tr")[i].querySelectorAll("td")[j].classList;
        }
    }
    return array;
}
function getValidMoves(array) {
    var validMoves = [];
    for (let i = 0; i < array.length; i++) {
        for (let j = 0; j < array[i].length; j++) {
            if (array[i][j].contains("white")) {
                validMoves = validMoves.concat(getValidMovesForPiece(array, i, j));
            }
        }
    }
    return validMoves;
}
function tableToPythonEncoded(table, move) {
    let array = tableToArray(table);
    var pythonEncoded = "";
    for (let i = 0; i < array.length; i++) {
        for (let j = 0; j < array[i].length; j++) {
            if (array[i][j].contains("white")) {
                if (array[i][j].contains("pawn")) {
                    pythonEncoded += "P";
                }
                else if (array[i][j].contains("bishop")) {
                    pythonEncoded += "B";
                }
                else if (array[i][j].contains("knight")) {
                    pythonEncoded += "N";
                }
                else if (array[i][j].contains("rook")) {
                    pythonEncoded += "R";
                }
                else if (array[i][j].contains("queen")) {
                    pythonEncoded += "Q";
                }
                else if (array[i][j].contains("king")) {
                    pythonEncoded += "K";
                }
            } else if (array[i][j].contains("black")) {
                if (array[i][j].contains("pawn")) {
                    pythonEncoded += "p";
                }
                else if (array[i][j].contains("bishop")) {
                    pythonEncoded += "b";
                }
                else if (array[i][j].contains("knight")) {
                    pythonEncoded += "n";
                }
                else if (array[i][j].contains("rook")) {
                    pythonEncoded += "r";
                }
                else if (array[i][j].contains("queen")) {
                    pythonEncoded += "q";
                }
                else if (array[i][j].contains("king")) {
                    pythonEncoded += "k";
                }
            } else {
                pythonEncoded += "-";
            }
        }
    }
    return pythonEncoded;
}
function modifyArrayWithMove(array, move) {
    var newArray = array;
    newArray[move[1][0]][move[1][1]] = newArray[move[0][0]][move[0][1]];
    for (row of newArray) {
        for (cell of row) {
            if (cell.contains("empty")) {
                newArray[move[0][0]][move[0][1]] = cell;
                break;
            }
        }
    }
    return newArray;
}
function isCheck(array) {
    var validMoves = [];
    for (let i = 0; i < array.length; i++) {
        for (let j = 0; j < array[i].length; j++) {
            if (array[i][j] != "empty" && array[i][j].contains("black")) {
                validMoves = validMoves.concat(getValidMovesForBlackPiece(array, i, j));
            }
        }
    }
    for (let move of validMoves) {
        if (array[move[0]][move[1]].contains("king") && array[move[0]][move[1]].contains("white")) {
            console.log(move)
            return true;
        }
    }
    return false;
}
function getValidMovesForBlackPiece(array, x, y) {
    // copy getValidMovesForPiece change "white" to "black" and "black" to "white"
    let validMoves = [];
    let piece = array[x][y];
    if (piece.contains("pawn" && x-1 >= 0)) {
        if (array[x + 1][y].contains("empty")) {
            validMoves.push([x + 1, y]);
            if (x == 1 && array[x + 2][y].contains("empty")) {
                validMoves.push([x + 2, y]);
            }

        }
        if (array[x + 1][y + 1].contains("white")) {
            validMoves.push([x + 1, y + 1]);
        }
        if (array[x + 1][y - 1].contains("white")) {
            validMoves.push([x + 1, y - 1]);
        }
    }
    if (piece.contains("knight")) {
        directions = [[2,1],[1,2]]
        negatives = [[1,1],[1,-1],[-1,1],[-1,-1]]
        for (let dir of directions) {
            for (let neg of negatives) {
                move = [x+dir[0] * neg[0], y+dir[1] * neg[1]];
                if (move[0] >= 0 && move[0] < 8 && move[1] >= 0 && move[1] < 8) {
                    if (!array[move[0]][move[1]].contains("black")) {
                        validMoves.push(move);
                    }
                }
            }
        }
    }
    if (piece.contains("rook") || piece.contains("queen")) {
        directions = [[1,0],[-1,0],[0,1],[0,-1]]
        for (let dir of directions) {
            pos = [x + dir[0], y + dir[1]];
            while (pos[0] >= 0 && pos[0] < 8 && pos[1] >= 0 && pos[1] < 8) {
                if (array[pos[0]][pos[1]].contains("black")) {
                    break;
                } else if (array[pos[0]][pos[1]].contains("white")) {
                    validMoves.push(pos);
                    break;
                } else {
                    validMoves.push(pos);
                }
                pos = [pos[0] + dir[0], pos[1] + dir[1]];
            }
        }
    }
    if (piece.contains("bishop") || piece.contains("queen")) {
        directions = [[1,1],[-1,1],[1,-1],[-1,-1]]
        for (let dir of directions) {
            pos = [x + dir[0], y + dir[1]];
            while (pos[0] >= 0 && pos[0] < 8 && pos[1] >= 0 && pos[1] < 8) {
                if (array[pos[0]][pos[1]].contains("black")) {
                    break;
                } else if (array[pos[0]][pos[1]].contains("white")) {
                    validMoves.push(pos);
                    break;
                } else {
                    validMoves.push(pos);
                }
                pos = [pos[0] + dir[0], pos[1] + dir[1]];
            }
        }
    }
    if (piece.contains("king")) {
        x_dir = [-1,0,1];
        y_dir = [-1,0,1];
        for (let x_ of x_dir) {
            for (let y_ of y_dir) {
                if (x_==0 && y_==0) {continue}
                pos = [x + x_, y + y_];
                if (pos[0] >= 0 && pos[0] < 8 && pos[1] >= 0 && pos[1] < 8) {
                    if (!array[pos[0]][pos[1]].contains("black")) {
                        validMoves.push(pos);
                    }
                }

            }
        }
    }
return validMoves
}
function getValidMovesForPiece(array,x,y) {
    let validMoves = [];
    let piece = array[x][y];
    if (piece.contains("pawn") && x-1 >= 0) {
        if (array[x-1][y].contains("empty")) {
            validMoves.push([[x,y],[x-1,y]]);
            if (x == 6 && array[x-2][y].contains("empty")) {
                validMoves.push([[x,y],[x-2,y]]);
            }
        }
        if(y-1 >= 0 && array[x-1][y-1].contains("black")) {
            validMoves.push([[x,y],[x-1,y-1]]);
        }
        if(y+1 < 8 && array[x-1][y+1].contains("black")) {
            validMoves.push([[x,y],[x-1,y+1]]);
        }
    }
    if (piece.contains("knight")) {
        directions = [[2,1],[1,2]]
        negatives = [[1,1],[1,-1],[-1,1],[-1,-1]]
        for (let dir of directions) {
            for (let neg of negatives) {
                move = [x+dir[0]*neg[0],y+dir[1]*neg[1]];
                if (move[0] >= 0 && move[0] < 8 && move[1] >= 0 && move[1] < 8) {
                    if (!array[move[0]][move[1]].contains("white")) {
                        validMoves.push([[x,y],[move[0],move[1]]]);
                    }
                }
            }
        }
    }
    if (piece.contains("rook") || piece.contains("queen")) {
        directions = [[1,0],[-1,0],[0,1],[0,-1]]
        for (let dir of directions) {
            pos = [x + dir[0],y + dir[1]];
            while (pos[0] >= 0 && pos[0] < 8 && pos[1] >= 0 && pos[1] < 8) {
                if (array[pos[0]][pos[1]].contains("white")) {
                    break;
                }
                if (array[pos[0]][pos[1]].contains("black")) {
                    
                    validMoves.push([[x,y],[pos[0],pos[1]]]);
                    break;
                } else {
                    validMoves.push([[x,y],[pos[0],pos[1]]]);
                }
                pos[0] += dir[0];
                pos[1] += dir[1];
            }
        }
    }
    if(piece.contains("bishop") || piece.contains("queen")) {
        directions = [[1,1],[-1,1],[1,-1],[-1,-1]]
        for (let dir of directions) {
            pos = [x + dir[0],y + dir[1]];
            while (pos[0] >= 0 && pos[0] < 8 && pos[1] >= 0 && pos[1] < 8) {
                if (array[pos[0]][pos[1]].contains("white")) {
                    break;
                }
                if (array[pos[0]][pos[1]].contains("black")) {
                    
                    validMoves.push([[x,y],[pos[0],pos[1]]]);
                    break;
                } else {
                    validMoves.push([[x,y],[pos[0],pos[1]]]);
                }
                pos[0] += dir[0];
                pos[1] += dir[1];
            }
        }
    }
    if(piece.contains("king")) {
        x_dir = [1,0,-1];
        y_dir = [1,0,-1];
        for (let x_ of x_dir) {
            for (let y_ of y_dir) {
                if (x_ == 0 && y_ == 0) {continue}
                pos = [x + x_,y + y_];
                if (pos[0] >= 0 && pos[0] < 8 && pos[1] >= 0 && pos[1] < 8) {
                    if (!array[pos[0]][pos[1]].contains("white")) {
                        validMoves.push([[x,y],[pos[0],pos[1]]]);
                    }
                }
            }
        }
    }
return validMoves
}
let playersTurn = true;
let selected = null;
let indexCell = (x,y) => document.querySelectorAll("tr")[x].querySelectorAll("td")[y];
let initCell = (x,y) => {
    let cell = indexCell(x,y);
    cell.addEventListener('click', async () => {
        if (!playersTurn) {return}
        if (cell.classList.contains("white")) {
            if (selected && !cell.classList.contains("selected")) {
                selected.classList.remove("selected");
                selected = null;
            }
            if (cell.classList.contains("selected")) {
                cell.classList.remove("selected");
                for (let cell of document.querySelectorAll(".moveTo")) {
                    cell.classList.remove("moveTo");
                }
                return
            }
            cell.classList.toggle("selected");
            for (let cell of document.querySelectorAll(".moveTo")) {
                cell.classList.remove("moveTo");
            }
            selected = cell;

            moves = getValidMovesForPiece(tableToArray(document),x,y);
            for (let move of moves) {
                if (!isCheck(modifyArrayWithMove(tableToArray(document),move))) {
                    indexCell(move[1][0],move[1][1]).classList.add("moveTo");
                }
            }
            
        }
        if (cell.classList.contains("moveTo")) {
            for (let cell of document.querySelectorAll("td")) {
                cell.classList.remove("moveTo");
                cell.classList.remove("prevTo");
                cell.classList.remove("prevFrom");
            }
            selected.classList.remove("selected");
            console.log(selected);
            cell.classList = selected.classList;
            console.log("ADD TO SELECTED");
            console.log(selected);
            cell.classList.add("prevTo");
            selected.classList = "empty prevFrom";
            selected = null;
            playersTurn = false;
            data = await fetch(`/api/${tableToPythonEncoded(document)}`, {method: "GET"})
            data = await data.json()
            from = indexCell(data[0][0],data[0][1]);
            to = indexCell(data[1][0],data[1][1]);
            for (let cell of document.querySelectorAll("td")) {
                cell.classList.remove("prevTo");
                cell.classList.remove("prevFrom");
            }
            to.classList = from.classList;
            to.classList.add("prevTo");
            from.classList = "empty prevFrom";
            playersTurn = true;
        }
    });
}
(function() {
    for (let x = 0; x < document.querySelectorAll("tr").length; x++) {
        row = document.querySelectorAll("tr")[x];
        for (let y = 0; y < row.querySelectorAll("td").length; y++) {
            initCell(x,y);
        }
    }
})();