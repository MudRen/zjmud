// didao5.c

inherit ROOM;

void create()
{
	set("short", "��");
	set("long", @LONG
��һ�����ӭ����ŵ�һ�ɸ��õ�������ζ����������ǰ���
�����У����ֿ�����ϣ�����㲻����ʼ�ӿ�Ų����뿴�����ﵽ����
Щʲô������ 
LONG
	);
	set("exits", ([ /* sizeof() == 2 */
		"north" : __DIR__"didao6",
		"south" : __DIR__"didao4",
		"east"  : __DIR__"didao4",
		"west"  : __DIR__"didao5",
	]));

	setup();
}
