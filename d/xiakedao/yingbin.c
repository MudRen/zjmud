// yingbin.c ӭ����

inherit ROOM;

void create()
{
	set("short", "ӭ����");
	set("long", @LONG
����һ��ʯ�������µ���ʯ���̵��������룬������һЩľ�Ƽ�
�ߣ��������䲢������֮��������ʰ�øɸɾ�����һ����Ⱦ��������
һ��С�Ե꣬��������Ϣ�ҡ�
LONG );
	set("exits", ([
	       "east" : __DIR__"xiaodian",
	       "west" : __DIR__"xiuxis",
	       "south" : __DIR__"shidong2",
	       "out" : __DIR__"dongmen",
	]));
	setup();
}
