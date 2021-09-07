// Room: guangchang.c
// Date: Feb.14 1998 by Java

inherit ROOM;
void create()
{
	set("short", "�ᶽ����");
	set("long", @LONG
������ᶽ���š�Ρ����ΰ�ĳ�ǽ�ϣ� "�ɶ��ᶽ��" �������
ʮ�����ۣ����ƻԻ͡������ױ��������ԡ�
LONG );
	set("outdoors", "chengdu");
	set("exits", ([
	    "south" : __DIR__"guangchang",
	    "north" : __DIR__"tidufu",
	]));
	set("objects", ([
	    __DIR__"npc/qinbing" : 2,
	]));
	setup();
}

int valid_leave(object me, string dir)
{
	int i;
	object bing;

	bing = present("qin bing", environment(me));
	if (dir != "north" || ! objectp(bing) || ! living(bing))
		return ::valid_leave(me, dir);

	if (me->query("weiwang") >= 10000)
	{
		message_vision("$NЦ������" + RANK_D->query_respect(me) +
			       "���������������ȥ����ͨ������\n", bing, me);
		return ::valid_leave(me, dir);
	}

	if (me->query("special_skill/trick"))
	{
		message_vision("$N����$n���˹�����������ס��"
			       "ȴ��$nһ���Ϻȣ���ɢ������\n"
			       "���ɵ�����һ����ڨڨ�Ĳ���˵����\n", bing, me);
		return ::valid_leave(me, dir);
	}

	return notify_fail("�ױ���ǰ��ס�㣬����˵������λ"  +
			   RANK_D->query_respect(me) + "��ذɡ���ү�����͡�\n");
}
