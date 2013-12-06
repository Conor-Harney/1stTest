var healthPickUp = function(posXIn, posYIn){
	this.worldPosX = posXIn;
	this.worldPosY = posYIn;//the position in the world
	this.relScreenPosX = this.worldPosX;
	this.relScreenPosY =  this.worldPosY;
	this.size = 50;
	this.alive = true;
	this.healthValue = 1;
};

healthPickUp.prototype.update = function(screenPosX, screenPosY){
	if(this.alive == true){
		this.relScreenPosX = this.worldPosX + screenPosX;
		this.relScreenPosY = this.worldPosY + screenPosY;
	}
};

healthPickUp.prototype.getPosition = function(){
	if(this.alive == true){
		return this.relScreenPosX, this.relScreenPosY;
	}
};

healthPickUp.prototype.destroy = function(){
	this.alive = false;
};

healthPickUp.prototype.checkCollision = function(playersPositionX, playersPositionY, playerSizeX, playerSizeY){
	if(this.alive == true){
	
		if(playersPositionX > this.relScreenPosX + this.size ||
			playersPositionX + playerSizeX < this.relScreenPosX ||
			playersPositionY > this.relScreenPosY + this.size ||
			playersPositionY + playerSizeY < this.relScreenPosY){return false;}
			else{
				this.destroy();
				return this.healthValue;
			}
	}			
};


healthPickUp.prototype.draw = function()
{
	if(this.alive == true)
	{
		//ctx.fillStyle = rgb(255, 0, 0);
		//ctx.fillRect(this.relScreenPosX, this.relScreenPosY, this.size, this.size);
		//-

		var img2 = AM.cache["images/healthPack.gif"];
		//img2.addEventListener('load', function () {
		//	var x2 = 0, y2 = 200;
			ctx.drawImage(img2, this.relScreenPosX, this.relScreenPosY, this.size, this.size);
		//}, false);

		
		
	}
};