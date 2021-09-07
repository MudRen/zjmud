// /d/xingxiu/nanjiang.c

inherit ROOM;

void create()
{
	set("short", "�Ͻ�ɳĮ");
	set("long", @LONG
����Ǻ�嫵���������ɴ�ɳĮ��һ�߽�������·���ʧ�˷���
��е�����ʮ�ֽ��ʣ����ǿ�Щ�뿪�ɡ�
LONG );

	set("exits", ([
	    "northeast" : __DIR__"shanjiao",
	    "southeast" : __FILE__,
	    "southwest" : __FILE__,
	    "northwest" : __DIR__"nanjiang1",
	    "north" : __FILE__,
	    "west" : __FILE__,
	    "south" : __FILE__,
	    "east" : __FILE__,
	]));

	set("outdoors", "xiyu");
	set("no_map", "����ĵ��������Ի��޷����Ƶ�ͼ��\n");

	setup();
}

int valid_leave(object me, string dir)
{
	int current_water;

	if (! interactive(me))
		return ::valid_leave(me, dir);

	current_water = me->query("water");
	if (current_water == 0)
	{
	  	write("���Ѿ��е������ˣ�ڤڤ����������˰���̧����ɽ���¡�\n");
	  	me->move(__DIR__"shanjiao");
	  	me->unconcious();
		return -1;
	}

	if (current_water <= 20)
	{
	    	write("�����ȱˮ����ð���ǡ�\n");
	    	me->set("water", 0);
	} else
	    	me->add("water", -20);

	if (random(2))
	{
		me->move(sprintf(__DIR__"nanjiang%d", random(3) + 1));
		return -1;
	}

	return ::valid_leave(me, dir);
}
