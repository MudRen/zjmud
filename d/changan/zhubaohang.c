//Room: zubaohang.c

inherit ROOM;

void create ()
{
	set ("short", "�鱦��");
	set ("long", @LONG
�鱦������ⱦ�����䣬ѣ������Щ�������۾������µĳ����г�
���Ÿ��������鱦�������������м������ſ�����ѡ�����鱦��һ����
��ľ���ϰ��ſ����߶�ߵ����������֮����͸�ŵ������������ۺ���
֮����
LONG);
	set("exits", ([
		"south" : __DIR__"yongtai-beikou",
	]));
	set("objects", ([
		__DIR__"npc/jinfuhuan"  : 1,
	]));

	setup();
}
