// corpse_box.c
inherit ITEM;
#include <ansi.h>
void create()
{
	set_name(HIM"��Ը��"NOR,({"lack card","card"}));
	set_weight(1000);
	if( clonep() )
		set_default_object(__FILE__);
	else
       {
	    set("long","����<"+this_object()->query("name")+">,\n"ZJURL("cmds:xuyuan lack card")ZJSIZE(15)"���Ը"NOR"���԰�!\n");
	    set("unit","��");
	}
}
void init()
{
	if (environment()==this_player())
	add_action("do_xuyuan","xuyuan lack card",1);
}
//�򿪱���ĺ���
int do_xuyuan()
{
	int i;
   int num=1;
   string obj=""; 
   object ob;

  
	object me = this_player();
	if (me->is_busy())
		{ write("����һ������δ��ɣ�\n"); return 1;}
	if( me->is_fighting() )
		{ write("ս����ʹ����Ը��������ѽ��\n"); return 1;}
	message_vision("$N˫��ץ��["+this_object()->query("name")+"],��������˿��и��ֵ����֣�"NOR"\n",me);
	i=random(100);
	if(i > 0 && i <= 50)
	{
		ob = new("/clone/box/chuji_box"); 
	}
	else if(i > 50 && i <= 80)
	{
		ob = new("/clone/box/zhongji_box"); 
	}
	else if(i > 80 && i <= 90)
	{
		ob = new("/clone/box/gaoji_box"); 
	}
	else if(i > 90 && i <= 93)
	{
		ob = new("/clone/box/chaoji_box"); 
	}
	else if(i == 99)
	{
		ob = new("/clone/box/vip_box"); 
	}
	else
	{
		tell_object(me,""HIR"<....>"NOR"��*��Ը��*��Ϊ..."WHT"һ�ѷ�ĩ"NOR"\n");
		return 1;
	}
	tell_object(me,""HIM"*****************************************************\n");
	tell_object(me,""HIR"��ϲ"NOR"��["+this_object()->query("name")+"]��Ϊ..."+chinese_number(num)+ob->query("unit")+HIG+"<< "+ob->query("name")+HIG" >>"+NOR+"\n");
	tell_object(me,""HIM"*****************************************************"NOR"\n");
	ob->move(me); 
	destruct(this_object());
	return 1;
}

int query_autoload()
{
	return 1;
}