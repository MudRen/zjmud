#include <ansi.h>

inherit ITEM; 

void create()
{
	set_name ("Ǯ����", ({ "qiandai zi"}));
	if( clonep() )
		set_default_object(__FILE__);
	else {
	set("long","����һ��Ǯ���ӣ�"ZJURL("cmds:open qiandai zi")+ZJSIZE(20)+HIY"��"NOR"���ܹ����һЩ��Ǯ��\n");
	set("unit","��");
	set_weight(100);
	set("value",10000);
	setup();
     }
}


void init()
{
	add_action("do_read","open");
  
}

int do_read(string arg)
{
	object me=this_player();
	object ob1;
	int i,k;
	i=1+random(5);    

	if (!arg)
      		return notify_fail("��Ҫ��ʲô��\n");
      		
	if (arg!="qiandai zi")
      		return notify_fail("��Ҫ��ʲô��\n");

        message_vision("$N����һ��$n��"NOR"\n", me, this_object()); 	

	ob1 = new("/clone/money/gold");
	ob1->set_amount(i);
	ob1->move(me); 

	tell_object(me,YEL"������"+chinese_number(i)+"���ƽ�!"NOR"\n");
	destruct(this_object());
	return 1;
}	 
