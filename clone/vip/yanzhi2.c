inherit ITEM;
#include <ansi.h>

void create()
{
	set_name(HIR"���ݵ�"NOR, ({"huirong dan"}));
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("value", 100000);
		set("yuanbao", 100);
                set("no_sell",1);
		set("unit", "��");
		set("long","����һ�����ݵ���"ZJURL("cmds:use huirong dan")ZJSIZE(20)"����"NOR"֮����������!\n");

	}
}

void init()
{
    if (environment()==this_player())
    	add_action("on_used","use");
}

int on_used(string arg)
{
	object me=this_player();
	
	if (arg!="huirong dan")
      		return notify_fail("��Ҫ��ʲô?\n");  

        if (me->query("per")<11) return notify_fail("�����ò�Ѿ������ˡ�\n");

	me->add("per",-1-random(3));

        if (me->query("per")<11) me->set("per",10);

	write(YEL"�������һ��"HIR"���ݵ�"YEL"��������մ���"NOR"\n�����ڵ���ò�ǣ�"+me->query("per")+"��"NOR"\n");
	me->save();
	destruct(this_object());
	return 1;
}

int query_autoload() { return 1; }