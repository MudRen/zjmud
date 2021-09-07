// Room: /d/xingxiu/xxh1.c

inherit ROOM;

void create()
{
	set("short", "���޺�");
	set("long", @LONG
���������޺��ߡ�˵�Ǻ�����ʵ��Ƭ���������󣬵���ʮ���ն�
����ʯ����һ���ѷ�ͨ��һ��ɽ����
LONG );
	set("exits", ([
	     "north"   : __DIR__"xxh2",
	     "southup" : __DIR__"tianroad2",
	     "westup"  : __DIR__"tianroad3",
	     "east"  : __DIR__"jingji/enter",
	]));
	set("objects", ([
		CLASS_D("xingxiu")+"/zhaixing" : 1,
		__DIR__"npc/gushou"  : 1,
		__DIR__"npc/haoshou" : 1,
		__DIR__"npc/boshou" : 1,
	]) );
	set("outdoors", "xingxiu");
	set("valid_startroom", 1);
	setup();
}

int valid_leave(object me, string dir)
{
	object zhai;

	if (dir != "north" && dir != "westup")
	{
		return ::valid_leave(me, dir);
	} else
	{
		if (objectp(zhai = present("zhaixing zi", environment(me))) &&
		    living(zhai))
		{
			if (me->query("shen") > 100 && me->query("combat_exp") > 400000)
				return notify_fail("ժ���Ӻȵ�����λ" +
						   RANK_D->query_respect(me) + "���ߣ�\n");
		}
		return ::valid_leave(me, dir);
	}
}
