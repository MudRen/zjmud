//Room: fengxu5.c

inherit ROOM;

void create ()
{
	set ("short", "��ڼ��");
	set ("long", @LONG
��ڼ���ǳ��������Ĵ�֣���ʯ��·��ֱ����չ��ȥ��һ·������
�ȼ磬�ϸ账��������֮����ֱ�����ɾ��ء������������֣������ǳ�
���ǵ�Ѳ������
LONG);
	set("exits", 
	([ //sizeof() == 3
		"north" : __DIR__"fengxu4",
		"west" : __DIR__"qinglong3",
		"east" : __DIR__"xunbufang",
	]));

	set("outdoors", "changan");
	setup();
}
