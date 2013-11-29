var AM;
var game;
function main()
{
	//change version number if you suspect a problem with caching
	AM = new AssetManager;
	AM.queueDownload("images/healthPack.gif");
	AM.downloadAll(setup);
	
	
			
}

function setup() {
    console.log("version 1");
	this.game= new Game();

	this.game.initCanvas();
	//ctx the drawing context, which lets you draw onto the canvas
	//Most people call it ctx for short	
	ctx.clearRect(0, 0, canvas.width, canvas.height);
	

	this.game.initWorld();		
		
	//start game loop

}
