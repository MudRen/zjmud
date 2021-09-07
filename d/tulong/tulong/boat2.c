#include <ansi.h>
inherit ROOM;

void create()
{
	set("short","����");
	set("long",@LONG
��Щ�󴬣����Ǿ޾����ɳ��һ���˵�������
LONG );
	set("exits",([
		"northup":__DIR__"daobian",
	]));

	set("objects",([
		 __DIR__"obj/stone": 1,
	]));
	setup();
}

void init()
{
	add_action("do_break","break");
}

int do_break(string arg)
{
	object me=this_player(),inv;
	if (arg!="boat" && arg!="��") return notify_fail("��Ҫ����ʲô��\n");
	inv=present("stone",me);
	if (query("dao")) return notify_fail("���ϵ�Φ����͵��ˣ�����ʲô��\n");
	if (!objectp(inv)) return notify_fail("��׼����ʲô�Ҵ�ѽ��\n");
	else 
	{
	message_vision("$N��������"+inv->query("name")+"�����ϵ�Φ����ȥ��\n",me);
	remove_call_out("do_dao");
	call_out("do_dao",3,me);
	return 1;
	}
}

int do_dao(object me)
{
	message_vision( WHT "\nֻ���ÿ���������֮�������������Ĵ�Φһ��������������\n����֮�����������֮�䣬��Φ�˻򵹻�б����һ���⡣"NOR"\n",me);
	set("dao",1);
	set("long","��Щ�󴬣����Ǿ޾����ɳ��һ���˵�������ֻ��Φ�˶����Ҷ��ˡ�\n");
	me->set_temp("dao",1);
	return 1;
}

