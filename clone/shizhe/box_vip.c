// chuji_box.c
inherit ITEM;
#include <ansi.h>
void create()
{
	set_name(HIR"VIP����"NOR,({"vipbox"}));
	set_weight(5000);
  
	if( clonep() )
		set_default_object(__FILE__);
	else
       {
	    set("long","����ϵͳ������"+this_object()->query("name")+",ʹ��(openbox vipbox)"ZJURL("cmds:openbox vipbox")ZJSIZE(15)"��"NOR"����!\n");
	    set("unit","��");
	    set("win_box",1);
	}
}
void init()
{
	if (environment()==this_player())
		add_action("do_openbox","openbox vipbox",1);
}
//�򿪱���ĺ���
int do_openbox()
{
	int i;
	int num=1;
	string obj=""; 
	object ob;

	//�������ǳ�������.����ϡ����ʯ,��֮��ʯ.
	string *box= ({
		"/clone/money/cash","/clone/gift/fjade","/clone/gift/fushougao","/clone/gift/god_eyes",
		"/clone/gift/feimao","/clone/gift/feidan","/clone/gift/fdiamond","/clone/gift/fcrystal",
		"/clone/gift/fagate","/clone/gift/shenliwan","/clone/gift/tianxiang",
		"/clone/gift/unknowdan","/clone/gift/xiandan","/clone/gift/xianxing","/clone/gift/xisuidan",
		"/clone/gift/jiuzhuan","/clone/gift/magate","/clone/gift/mcrystal","/clone/gift/mdiamond","/clone/gift/mjade",
	});
  
	object me = this_player();
	if (me->is_busy())
	      { write("����һ������δ��ɣ�\n"); return 1;}
	if( me->is_fighting() )
	      { write("ս���п����䣿����ѽ��\n"); return 1;}
       
	message_vision(HIM"$N�������["+this_object()->query("name")+"]�ĸ���,���仯Ϊһ��Ѫɫ�⻪��"NOR"\n",me);
	i=random((int)sizeof(box));
    
	ob = new(box[i]); 
	if(ob->query("base_value"))
	{
		num=random(1)+1;
		ob->set_amount(num);
	}
	tell_object(me,""HIR"******************************************************\n");
	tell_object(me,""HIR"��ϲ: "NOR"���["+this_object()->query("name")+"]�еõ���..."+chinese_number(num)+ob->query("unit")+HIR+"<< "+ob->query("name")+HIR+" >>"+NOR+"\n");
	tell_object(me,""HIR"*****************************************************"NOR"\n");
	ob->move(me); 
	destruct(this_object());
	return 1;
}
int query_autoload()
{
	return 1;
}