//Room: qunyuys6.c

inherit ROOM;

void create()
{
	set("short", "Ⱥ��¥����");
	set("long", @LONG
һ�����ҡ����з���һ�Ŵ󴲣����������廨�Ľ�������ͷ������
�������£��������������һ��Ϸˮԧ�죬��ɫ���ã����������
�ϵ���һ�����򣬺�������һ��������һֻ��ױ���ӡ���ǰ����������
����Ь��һ���еģ�һ��Ů�ģ����Ŷ��á�
LONG);
	set("exits", ([ /* sizeof() == 1 */
		"north" : __DIR__"qunyulou3",
	]));
	set("objects", ([
		__DIR__"npc/lanyi" : 1,
	]) );

	setup();
}
