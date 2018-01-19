/*
window.onload = function(){
 // alert("onload");
    var obutton = document.getElementById('signin');
    var oUser = document.getElementById('user');
    var oPswd = document.getElementById('pswd');
    var oRemember = document.getElementById('remember');
    var oCheck = document.getElementById('checkMsg');
    //页面初始化时，如果帐号密码cookie存在则填充
    if(getCookie('user') && getCookie('pswd')){
      //alert("getCookie");
      oUser.value = getCookie('user');
      oPswd.value = getCookie('pswd');
      oRemember.checked = true;
    }
    //复选框勾选状态发生改变时，如果未勾选则清除cookie
    oRemember.onchange = function(){
      if(!this.checked){
        delCookie('user');
        delCookie('pswd');
      }
    };
	//表单提交事件触发时，如果复选框是勾选状态则保存cookie
     if(oRemember.checked){ 
        setCookie('user',oUser.value,7); //保存帐号到cookie，有效期7天
        setCookie('pswd',oPswd.value,7); //保存密码到cookie，有效期7天
      }
};
*/
function login(){
      //验证用户名和密码
	    var oUser = document.getElementById('user');
		var oPswd = document.getElementById('pswd');
      var argu0 = "?operation=check&username=" + oUser.value + "&password=" + oPswd.value;
	 // alert(argu);
      var encodeArgu0 = escape(argu0);
     // alert(encodeArgu);

	  $.get(encodeArgu0, function(data, status){
        if(status=="success"){
			if(data == "wrong username." || data == "wrong password.")
			{
				//alert(data);
				var oCheck = document.getElementById('checkMsg');
				oCheck.hidden = false;
			}
			else
			{
				setCookie('user',oUser.value,7);
				setCookie('pswd',oPswd.value,7);
				//$("#main_html").empty();
				//$("#main_html").append(data);
				var argu = "?operation=login&username=" + oUser.value + "&password=" + oPswd.value;
				// alert(argu);
				var encodeArgu = escape(argu);
    
				var element = document.getElementById("hideLink");
				element.setAttribute("href", encodeArgu);
				if(/msie/i.test(navigator.userAgent))
				{
					element.fireEvent("onclick");
				}
				else
				{
					var e = document.createEvent("MouseEvents");
					e.initEvent("click", true, true);
					element.dispatchEvent(e);
				}
			}
		}
	  });
	
}

  //设置cookie
function setCookie(name,value,day){
    //alert("setCookie");
    //alert(name);
    //alert(value);
    var date = new Date();
    date.setDate(date.getDate() + day);
    //alert(date);
    document.cookie = name + '=' + value + ';expires='+ date;
    //alert("document.cookie");
    //alert(document.cookie);
  }
/*
  //获取cookie
  function getCookie(name){
    //alert("getCookie");
    //alert(name);
    var reg = RegExp(name+'=([^;]+)');
    var arr = document.cookie.match(reg);
    if(arr){
      //alert("cookie got");
      return arr[1];
    }else{
      //alert("no cookie");
      return '';
    }
  }
  //删除cookie
  function delCookie(name){
    //alert("delCookie");
    setCookie(name,null,-1);
  }
*/
