//Room: baihu3.c

inherit ROOM;

void create ()
{
	set ("short", "�׻���");
	set ("long", @LONG
�������ǳ��������Ĵ�֣���ʯ��·��ֱ����չ��ȥ��һ·������
�ȼ磬�ϸ账��������֮����ֱ�����ɾ��ء����涫�ߴ������ʵĶ���
���������ǵ�����ѧ�����Ӽࡣ
LONG);
	set("exits", 
	([ //sizeof() == 3
		"north" : __DIR__"guozijian",
		"west" : __DIR__"baihu2",
		"east" : __DIR__"fengxu1",
	]));

	set("outdoors", "changan");
	setup();
}
