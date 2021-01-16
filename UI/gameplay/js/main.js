   
//#region BINDING
    let centered = true;

    let gameplay = {
        homeScore: 0,
        awayScore: 0,
        gameClock: "00:00",
        stickDir: "C",
        bOffense: true,
        shotClock: 0,
        message: "",
        weardownBar: 100,
    };

    let bindings = $.bindings(gameplay);

//#endregion BINDING

function format(time) {   
    // Hours, minutes and seconds
    var hrs = ~~(time / 3600);
    var mins = ~~((time % 3600) / 60);
    var secs = ~~time % 60;

    // Output like "1:01" or "4:03:59" or "123:03:59"
    var ret = "";
    if (hrs > 0) {
        ret += "" + hrs + ":" + (mins < 10 ? "0" : "");
    }
    ret += "" + mins + ":" + (secs < 10 ? "0" : "");
    ret += "" + secs;
    return ret;
}

//#region WEARDOWNBAR
function tickBar(){
    setInterval(()=>{
        let progress = document.querySelector('#weardown-bar');
        let updatesPerSecond = 1000 / 30;

        var height = document.getElementById('weardown-bar').offsetHeight;
        var parentHeight = document.getElementById('weardown-bar').offsetParent.height;
        var percent = Math.ceil(100*height/parentHeight);
      
        function animator () { 
            if(percent !== bindings.weardownBar){
                 $(progress).css('width', bindings.weardownBar+'%');
            }
        }
      
        setTimeout(() => {
          animator();
        }, updatesPerSecond);

    }, 1000);
}

tickBar();
//#endregion

//#region UI CONTROLS 

    var homeScoreboard = document.getElementById('home-score');
    var awayScoreboard = document.getElementById('away-score');

    var homeScoreboard = document.getElementById('home-score');
    var awayScoreboard = document.getElementById('away-score');

    var actionDiv = document.getElementById('action-div');
    var joyDiv = document.getElementById('joy-div');


    setInterval(function(){ 
        
        let dir = bindings.stickDir
        triggerUE4EventMap('moveEvent', `PanDirection:${dir}`);
        // console.log('move dir', dir)

    }, 30);


    // We create a manager object, which is the same as Hammer(), but without the presetted recognizers. 
    var mcAction= new Hammer(actionDiv);

    mcAction.on("press", function(ev) {
        onShootStart();
        // console.log('actionDiv ', ev.type);
    });

    mcAction.on("pressup", function(ev) {
        onShootEnd();
        // console.log('actionDiv ', ev.type);
    });

    mcAction.on("tap", function(ev) {
        onAction();
        // console.log('actionDiv ', ev.type);
    })

    mcAction.on("panend panup pandown", function(ev) {
        switch(ev.type){
            case "panend":
                bindings.stickDir = "C";
                break;
            
            case "panup":
                bindings.stickDir = "N";
                break;
            
            case "pandown":
                bindings.stickDir = "S";
                break;
            default:
                break;
        }
        // console.log('joystick ', ev.type);
    })

    function onPan(direction) {
        triggerUE4EventMap('moveEvent', `PanDirection:${direction}`);
    }

    function onShootStart() {
        triggerUE4EventMap('shootStartEvent');
    }

    function onShootEnd() {
        triggerUE4EventMap('shootEndEvent');
    }

    function onAction() {
        triggerUE4EventBlank('actionEvent');
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

    function updateBar(value){
        bindings.weardownBar = value;
    }
    
    function updateShotClock(value){
        bindings.shotClock = value;
    }

    function updateGameClock(value){
        let str = format(value)
        bindings.gameClock = str;
    }

    function clearMessage(){
        bindings.message = "";
    }
//#endregion