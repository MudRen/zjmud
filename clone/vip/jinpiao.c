inherit ITEM;
#include <ansi.h>

void create()
{
	set_name(HIY"��Ʊ"NOR, ({"jin piao"}));
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("value", 10000000);
		set("yuanbao", 200);
                set("no_sell",1);
		set("unit", "��");
		set("long","����һ�Ž�Ʊ��"ZJURL("cmds:duihuan jin piao")ZJSIZE(20)"�һ�"NOR"֮����Ի��һǧ���ƽ�!\n");
		set("spectxt", "�һ�����һǧ���ƽ�\n");
	}
}

void init()
{
    if (environment()==this_player())
    	add_action("do_use","duihuan");
}

int do_use(string arg)
{
	object me=this_player();

	if (arg!="jin piao")
      		return notify_fail("��Ҫ�һ�ʲô?\n");  

        me->add("balance",10000000);
	write(YEL"�һ��ɹ������Ǯׯ�˻�������һǧ���ƽ�"NOR"\n");
	destruct(this_object());
	return 1;
}

int query_autoload() { return 1; }