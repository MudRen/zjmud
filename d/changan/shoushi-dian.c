//Room: shoushi-dain.c

inherit ROOM;

void create()
{
	set("short", "���ε�");
	set("long", @LONG
һ�����εꡣ���ε��ڷ���һ���������ӣ������ϰ��м�̴ֻ��
ľ�У�������ȫ���ŵģ�������ֽ�������������ȫ���������ۻ���
�ң����ε���ϰ����ڲ����
LONG);
	set("exits", ([ /* sizeof() == 1 */
		"south" : __DIR__"qixiang5",
	]));
	set("objects", ([
		__DIR__"npc/chen-laoban" : 1,
	]) );

	setup();
}
