//      dating.c ����
inherit ROOM;

void create()
{
	set("short", "����");
	set("long", @LONG
���������ڵĴ�������λ�е��ĸ�ɮ�ڸ������ۡ���
�����������ݵ䣬�������档
LONG );
	set("exits", ([
		"east" : __DIR__"zoulang1",
		"west" : __DIR__"zoulang2",
		"northeast" : __DIR__"chanshi",
		"southeast" : __DIR__"cangjing",
		"north" : __DIR__"cangjingge",
	]));
	set("objects", ([
		CLASS_D("xueshan")+"/fawang" :1,
	]));
	setup();
}

