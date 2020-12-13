   
//#region BINDING
    let centered = true;

    let gameplay = {
        homeScore: 0,
        awayScore: 0,
        message: "",
        weardownBar: 80,
    };

    let bindings = $.bindings(gameplay);

//#endregion BINDING

//#region WEARDOWNBAR
function updateBar(){
    setTimeout(()=>{
        let progress = document.querySelector('#weardown-bar')
        let interval = 1
        let updatesPerSecond = 1000 / 30
        let end = progress.max * 0.8
      
        function animator () {
            $(progress).css('width', bindings.weardownBar+'%');
        }
      
        setTimeout(() => {
          animator()
        }, updatesPerSecond)

    }, 1000)
}

updateBar()
//#endregion

//#region UI CONTROLS 

    var shootButton = document.getElementById('shoot-button');
    var stealButton = document.getElementById('steal-button');
    var blockButton = document.getElementById('block-button');
    var restartButton = document.getElementById('restart-button');

    var homeScoreboard = document.getElementById('home-score');
    var awayScoreboard = document.getElementById('away-score');

    var Joy1 = new JoyStick('joyDiv',{
        internalFillColor: 'rgba(24,24,28,0.15)',
        internalStrokeColor: 'rgba(24,24,28,0.15)',
        externalStrokeColor: 'rgba(24,24,28,0.15)'
    });

    setInterval(function(){ 
        
        let dir = Joy1.GetDir(); 
        triggerUE4EventMap('moveEvent', `PanDirection:${dir}`);

    }, 50);


    // We create a manager object, which is the same as Hammer(), but without the presetted recognizers. 
    var mcShoot = new Hammer(shootButton);

    mcShoot.on("press", function(ev) {
        onShootStart();
        shootButton.classList.add('transparent');
        //console.log('shootbutton ', ev.type);
    });

    mcShoot.on("pressup", function(ev) {
        onShootEnd();
        shootButton.classList.remove('transparent');
        void shootButton.offsetWidth;
        //console.log('shootbutton ', ev.type);
    });

    // We create a manager object, which is the same as Hammer(), but without the presetted recognizers. 
    var mcSteal= new Hammer(stealButton);

    mcSteal.on("tap", function(ev) {
        onSteal();
        stealButton.classList.remove('blink-2');
        void stealButton.offsetWidth;
        stealButton.classList.add('blink-2');
        //console.log('stealButton ', ev.type);
    });

    // We create a manager object, which is the same as Hammer(), but without the presetted recognizers. 
    var mcBlock= new Hammer(blockButton);

    mcBlock.on("tap", function(ev) {
        onBlock();
        blockButton.classList.remove('blink-2');
        void stealButton.offsetWidth;
        blockButton.classList.add('blink-2');
        //console.log('blockButton ', ev.type);
    });

    var mcRestart= new Hammer(restartButton);

    mcRestart.on("tap", function(ev) {
        onRestart();
        //console.log('restartButton ', ev.type);
    });

    function onPan(direction) {
        triggerUE4EventMap('moveEvent', `PanDirection:${direction}`);
    }

    function onShootStart() {
        triggerUE4EventMap('shootStartEvent');
    }

    function onShootEnd() {
        triggerUE4EventMap('shootEndEvent');
    }

    function onSteal() {
        triggerUE4EventBlank('stealEvent');
    }
    
    function onBlock() {
        triggerUE4EventBlank('blockEvent');
    }

    function onRestart() {
        triggerUE4EventBlank('restartEvent');
    }

//#endregion UI CONTROLS

//#region UE4 EVENTS
    function updateScore(home, away){
        
        if(home !== bindings.homeScore){
            homeScoreboard.classList.remove('heartbeat');
            void homeScoreboard.offsetWidth;
            homeScoreboard.classList.add('heartbeat');
        }
        else if(away !== bindings.awayScore){
            awayScoreboard.classList.remove('heartbeat');
            void awayScoreboard.offsetWidth;
            awayScoreboard.classList.add('heartbeat');
        }

        bindings.homeScore = home;
        bindings.awayScore = away;
        
    }

    function displayMessage(message){
        bindings.message = message;
    }

    function clearMessage(){
        bindings.message = "";
    }
//#endregion