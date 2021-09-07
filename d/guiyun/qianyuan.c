// Room: /guiyun/qianyuan.c
#include <ansi.h>;
inherit ROOM;

void create()
{
	set("short", "ǰԺ");
	set("long", @LONG
�����ǹ���ׯ��ǰԺ���൱�������ҿ�ǽ�����м���Ͱ���
ƽ�������Ǽ��˵�ס������ǰ��������ľ��������紵������Ҷ��
�����¡���ľ��������һ�������������һ�԰׵�(diao)��ԭ����
�����һ���Ϊ������ӻص��ġ�
LONG );
	set("outdoors", "guiyun");
	set("no_clean_up", 0);
	set("valid_startroom", 1);
	set("item_desc", ([
		"diao" : "һ�԰׵���չ�����ɡ�������һ����ĵ��ӣ�\n"
		"����(ride)�Ϳ��Էɻ��һ�����\n",
	]));

	set("exits", ([
		"out"   : __DIR__"damen",
		"north" : __DIR__"dating",
	]));
	setup();
}

void init()
{
	add_action("do_ride", "ride");
}
int do_ride()
{
	mapping myfam;
	object ob = this_player();

	myfam = (mapping)ob->query("family");
	if (! myfam || myfam["family_name"] != "�һ���")
	{
		message_vision("$NһԾ������˰׵�ֻ���׵����쳤ণ�ͻȻ��Ȼһ��...\n"
		HIR "���$N" HIR "ˤ�˸��������ף�"NOR"\n"
		"�����׵��$N��������Ȥ����ֻ��ʶ�һ����ĵ��ӡ�\n", ob);
		ob->receive_damage("qi", 50);
		ob->receive_wound("qi", 50);
		return 1;
	}

	if (objectp(query_temp("sb_ride"))) 
	{
		message_vision("���ڰ׵���æ��,���һ���ٳ�����\n", ob);
		return 1 ;
	}
	set_temp("sb_ride", ob);
	message_vision("$NһԾ������˰׵�ֻ���׵����쳤ণ�ͻȻչ��߷ɡ�\n\n"
		       "����һ��һ�����ν�����С������������\n", ob);
	ob->move("/d/taohua/lantian");
	tell_object(ob, CYN "\n�㲻�ϵط�ѽ�ɣ���ˮǧɽ����Ʈ��......"NOR"\n");
	call_out("taohua", 1, ob, environment(ob));
	return 1;
}

void taohua(object ob, object env)
{
	if (! objectp(ob))
		return;

	if (query_temp("sb_ride") == ob)
    		delete_temp("sb_ride");

	if (environment(ob) != env)
		return;

	tell_object(ob, "�����ڷɵ����һ�ɽׯ���׵�����������\n\n");
	ob->move("/d/taohua/damen");
}

