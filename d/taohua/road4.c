inherit ROOM;
 
void create()
{
	set("short", "С·");
	set("long",@LONG
����һ��ͨ����ɽ��С����С·���Գ������Ӳݡ��������Ǻ���������·��
������·����Ҳϡϡ����ð���˲�ѿ��������һ��Сɽ����
LONG);
	set("exits", ([
	    "east"   : __DIR__"road5",
	    "north"  : __DIR__"road2",
	]));
	set("objects", ([
	    "/clone/beast/dushe": 4,
	]) );

	set("resource/snake", ({ "/clone/beast/dushe", }));

	set("outdoors", "taohua");
	setup();
}
