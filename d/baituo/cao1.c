//room:cao1.c
inherit ROOM;

void create()
{
	set("short","�ݴ�");
	set("long",
		"�������Ҳݴԡ��������ȹ�����С���š�\n"
		"�������涼�������ߵ���ݣ������߳�û��\n"
	);

	set("exits",([
		"west" : __FILE__,
		"north" : __DIR__"cao2",
		"east" : __DIR__"ximen",
		"south" : __FILE__,
	]));

	set("objects",([
		"/clone/beast/jinshe" : random(2),
		"/clone/beast/snake" : 1,
	]));

	set("resource/snake", ({ "/clone/beast/jinshe",
				 "/clone/beast/qingshe", }));

	set("outdoors","baituo");
	setup();
}
