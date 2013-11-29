//These are global variables and are NOT recommended because they cause bad things to happen
//Some refactoring will be needed...
var canvas, ctx, player, b_gameOver, healthPack1, viewportPosY, cameraSpeed, lives, score;

function Game ()
{
	this.viewportPosY = 200;
	this.lives = 1;
	this.score = 0;
	this.cameraSpeed = 0.1;
}


Game.prototype.initWorld = function()
{
    //in initWorld, create the player object
    this.player = new Player(100, 100, 50, 50);
    this.goal = new Goal(000, 000, 50, 50);
	this.b_gameOver = false;
	this.healthPack1 = new healthPickUp(200, 200);
	playBackgroundLoop();
	
    //fill in suitable parameters<br>
    //draw the player by filling in the player's draw method
    //call the player's draw method from the game's draw method.<br>

}


Game.prototype.initCanvas=function () { 

	canvas = document.createElement('canvas'); 
	ctx = canvas.getContext('2d'); 

	document.body.appendChild(canvas);
	//set canvas to size of the screen.
	canvas.width = window.innerWidth; 
	canvas.height = window.innerHeight;
}


Game.prototype.update = function () {
    //in the update method in Game.js, check for keydown using:
    //console.log("in game update");
	ctx.clearRect(0, 0, canvas.width, canvas.height);
    if(KeyController.isKeyDown(Key.LEFT)) {
        this.player.moveLeft();
    }
    if (KeyController.isKeyDown(Key.RIGHT)) {
        this.player.moveRight();
    }
    if (KeyController.isKeyDown(Key.UP)) {
        this.player.moveUp();
    }
    if (KeyController.isKeyDown(Key.DOWN)) {
        this.player.moveDown();
    }
    
    if (this.player.checkCollision(this.goal)) {
        this.collisionReaction();
    } 
	this.cameraSpeed += 0.01;
	var healthAdder = this.healthPack1.checkCollision(this.player.x, this.player.y, this.player.width, this.player.height);
	if(healthAdder != false){this.health += healthAdder;}
	this.viewportPosY = this.viewportPosY - this.cameraSpeed;
	this.healthPack1.update(0,this.viewportPosY);	
	healthAdder = false;
	this.drawGUI();
}

/**
 *  @param e game entity
 */
Game.prototype.collisionResponse=function (e)
{
		
	
}


	
Game.prototype.gameLoop = function () 
{
    //console.log("in game gameloop");
	//viewportPosX += 1;
 	game.update(); 	 
	game.draw();
	window.requestAnimFrame(game.gameLoop);
}

Game.prototype.draw =function ()
{
    //sample 
    //console.log("in game draw");
    this.goal.draw();
	this.healthPack1.draw();
    this.player.draw();
	
}

Game.prototype.collisionReaction = function () {
    ctx.save();
    //add in your own colour
    ctx.fillStyle = rgb(0, 255, 0);
    //change this
    ctx.font = 'bold 20pt Tahoma';
    //otherwise bottom
    ctx.textBaseline = "top";
    //Put your message here; x and y are where the message will appear...
    ctx.fillText("Game over", 200, 100);
    //Any idea what save and restore do?
    ctx.restore();
	if(this.b_gameOver == false){
		play();
		this.b_gameOver = true;
	}
}

Game.prototype.drawGUI = function () {
	ctx.save();
    //add in your own colour
    ctx.fillStyle = rgb(0, 255, 0);
    //change this
    ctx.font = 'bold 20pt Tahoma';
    //otherwise bottom
    ctx.textBaseline = "top";
    //Put your message here; x and y are where the message will appear...
    ctx.fillText(this.health, 200, 0);
    //Any idea what save and restore do?
    ctx.restore();
}