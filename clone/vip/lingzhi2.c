inherit ITEM;
#include <ansi.h>

void create()
{
	set_name(HIM"С����"NOR, ({"xiaohuan dan"}));
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("value", 100000);
		set("yuanbao", 20);
                set("no_sell",1);
		set("unit", "��");
		set("long","����һ��С������"ZJURL("cmds:fu xiaohuan dan")ZJSIZE(22)"����"NOR"֮��������100��������Ϊ��ע�������������ã����ܳ���������������ޡ�\n");
	}
}

void init()
{
    if (environment()==this_player())
    	add_action("do_use","fu");
}

int do_use(string arg)
{
	object me=this_player();
	object ob1;
        int times;


  

	if (arg!="xiaohuan dan")
      		return notify_fail("��Ҫ����ʲô��\n");  

        if (me->query("max_neili") > me->query_neili_limit())
      		return notify_fail("���Ѿ�����ʹ��С����������������Ϊ�ˡ�\n"); 
 
	me->add("max_neili", 100);

        message_vision(me->query("name")+"����һ��"HIM"С����"NOR"���پ�����������"NOR"\n",me);
	destruct(this_object());
	return 1;
}

int query_autoload() { return 1; }