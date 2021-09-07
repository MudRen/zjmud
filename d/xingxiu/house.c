// /d/xingxiu/house.c
// Jay 3/26/96

inherit ROOM;

void create()
{
	set("short", "������Ժ");
	set("long", @LONG
����һ�������ҵ�ͥԺ���ſڴ���������Ͷ��Ժ������˾��ú����졣
Ժ�Ӷ����ǰ����Ŀ��������߾���С���֡�
LONG
	);
	set("exits", ([ 
	    "west" : __DIR__"beijiang",
	    "east" : __DIR__"house1",
	]));
	set("objects", ([
		__DIR__"npc/kid": 1,
		__DIR__"npc/bayi": 1
	]) );
	set("outdoors", "xingxiu");

	setup();
}

int valid_leave(object me, string dir)
{
	object bayi;

	if (objectp(bayi = present("ba yi", this_object())) && 
	    dir == "east" &&
	    ! me->query_temp("permit_pass/bayi"))
	{
		
		message_vision("$N˵���ҰѰ���������ҵĿ������ˣ�˭"
			       "Ҳ�����ȥ��\n", bayi);
		return 0;
	}

	return ::valid_leave(me, dir);
}

