// chuji_box.c
inherit ITEM;
#include <ansi.h>
void create()
{
	set_name(HIB"�м�����"NOR,({"boxno2"}));
	set_weight(5000);
	
	if( clonep() )
		set_default_object(__FILE__);
	else
       {
	    set("long",
		"����ϵͳ������"+this_object()->query("name")+",ʹ��(openbox boxno2)"ZJURL("cmds:openbox boxno2")ZJSIZE(15)"��"NOR"����!\n");
	    set("unit","��");
	   set("win_box",1);  //�Ƿ��ǽ���������
	}
}
void init()
{
    if (environment()==this_player())
    add_action("do_openbox","openbox boxno2",1);
}
//�򿪱���ĺ���
int do_openbox()
{
   int i;
   int num=1;
   string obj=""; 
   object ob;
  /*
   * ����,����ҩ,��ҩ,�˺���,�ǹ�,������װ,�ƴ�,����,���������ܼ�,���־�,,���̽�
  */
   string *box=
({
"/clone/money/silver","/clone/misc/fashao","/clone/misc/gaoyao","/clone/misc/shanghan","/clone/gift/tang","/clone/suit/new/new_boots","/clone/suit/new/new_pants", "/clone/suit/new/new_cloth","/clone/food/jiudai","/clone/food/jitui","/clone/book/basic-blade",
"/clone/book/basic-club","/clone/book/basic-dagger","/clone/book/basic-dodge","/clone/book/basic-force","/clone/book/basic-parry","/clone/book/basic-unarmed","/clone/book/basic-sword","/clone/book/basic-staff","/clone/book/basic-throwing",
"/clone/book/basic-whip","/clone/book/lbook1","/clone/weapon/green_sword",
"/clone/misc/xiaoshu","/clone/gift/icecream-chocolate","/clone/gift/icecream-vanilla",
"/clone/cloth/tiejia",
});
  
    object me = this_player();
	if (me->is_busy())
	      { write("����һ������δ��ɣ�\n"); return 1;}
	if( me->is_fighting() )
	      { write("ս���п����䣿����ѽ��\n"); return 1;}
       
    message_vision(HIB"$N�������["+this_object()->query("name")+"]�ĸ���,���仯Ϊһ����ɫ�⻪��"NOR"\n",me);
    i=random((int)sizeof(box));
    
    ob = new(box[i]); 
     if(ob->query("base_value"))
    {
       num=random(15)+1;
       ob->set_amount(num);
    }
  tell_object(me,""HIB"*****************************************************\n");
  tell_object(me,""HIR"��ϲ: "NOR"���["+this_object()->query("name")+"]�еõ���..."+chinese_number(num)+ob->query("unit")+HIB+"<< "+ob->query("name")+HIB+" >>"+NOR+"\n");
 tell_object(me,""HIB"*****************************************************"NOR"\n");
    ob->move(me); 
    destruct(this_object());
	return 1;
}
int query_autoload()
{
	return 1;
}