//room:cao2.c

inherit ROOM;

void create()
{
	set("short","�ݴ�");
	set("long",
		"�������Ҳݴԡ������������֡��������涼�������ߵ���ݣ�\n"
		"�����߳�û��\n"
	);

	set("exits",([
		"west" : __FILE__,
		"north" :__DIR__"zhulin",
		"east" : __DIR__"cao1",
		"south" : __DIR__"cao1",
	]));

	set("objects", ([
		"/clone/beast/qingshe" : random(2),
		"/clone/beast/jinshe" : random(2),
		"/clone/beast/dushe" : 1,
	]));

	set("resource/snake", ({ "/clone/beast/jinshe",
				 "/clone/beast/dushe",
				 "/clone/beast/qingshe", }));

	set("outdoors","baituo");
	setup();
}
