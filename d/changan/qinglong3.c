//Room: qinglong3.c

inherit ROOM;
void create ()
{
	set ("short", "������");
	set ("long", @LONG
�������ǳ��������Ĵ�֣���ʯ��·��ֱ����չ��ȥ��һ·������
�ȼ磬�ϸ账��������֮����ֱ�����ɾ��ء�������ǳ��������ܶ���
���ˡ���Ϊ���������������������ΰ��ܺã�����ϵ�����Ҳ����
��Ϊ��ȫ���ġ�
LONG);
	set("exits", 
	([ //sizeof() == 3
		"south" : __DIR__"yamen",
		"west" : __DIR__"qinglong2",
		"east" : __DIR__"fengxu5",
	]));

	set("outdoors", "changan");
	setup();
}
