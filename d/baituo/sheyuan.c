//room: sheyuan.c

inherit ROOM;

void create()
{
	set("short","��԰");
	set("long", @LONG
�����ǰ���ɽׯ����԰������ɽ�Զ��������£�����Ҫ��
���ʾ����Զ��ߡ����������ߣ�ǽ��Ҳ�����ߣ�������Ҳ��
�´����ߣ���֦��Ҳ�������ߣ������㲻�ľ���
LONG );
	set("exits",([
		"west"  : __DIR__"tuyuan",
	]));
	set("outdoors", "baituo");
	set("objects",([
		"/clone/beast/jinshe" : random(3),
		"/clone/beast/dushe"  : 1 + random(3),
		"/clone/beast/fushe"  : random(2),
		"/clone/beast/qingshe": random(2),
		"/clone/beast/wubushe": random(3),
	]));

	set("resource/snake", ({ "/clone/beast/jinshe",
				 "/clone/beast/dushe",
				 "/clone/beast/fushe",
				 "/clone/beast/wubushe",
				 "/clone/beast/qingshe", }));

	setup();
}
