//Room: biaoju-dating.c

inherit ROOM;

void create()
{
	set("short", "�����ھִ���");
	set("long", @LONG
�����еĳ��裬ȫ��ʮ�־��µ���̴ľ�Ҿߣ��������Ⱦ޴�İ�ߡ
���磬�������˸�ɫ�������ɼ��������İ���ͼ�����Ǻ����Ĺ��
����һ��Ƥ���Σ���������һ����ò���͵ĺ��ӡ�
LONG);
	set("exits", ([
		"north" : __DIR__"biaoju-dayuan",
	]));
	set("objects", ([
		__DIR__"npc/zong-biaotou" : 1,
	]) );

	setup();
}
