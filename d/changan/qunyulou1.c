//Room: qunyulou1.c

inherit ROOM;

void create()
{
	set("short", "Ⱥ��¥����");
	set("long", @LONG
Ⱥ��¥���������涼����ɴ���������ݺύ���ֳɴ�С��ʽ�Ļ�
�ƣ�ÿһ����һ��С������Ƕ�ţ��Ե���Ϊ���£������ڵƹ���ӳ��
�ԣ���ͷ��������÷������Ӱ��б��Ҳ���ڲ������ϡ���Ŀ�ĳ�������
������͸�룬΢��������������㣬������Ƣ��
LONG);
	set("exits", ([ /* sizeof() == 2 */
		"north" : __DIR__"qunyulou",
		"up"   : __DIR__"qunyulou2",
	]));
	set("objects", ([
		__DIR__"npc/lingfeixue" : 1,
	]) );

	setup();
}
