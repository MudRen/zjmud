// Room: /city/garments.c

inherit ROOM;
void create()
{
	set("short", "���µ��¥");
	set("long", @LONG
�����ǳ��µ�ĸ�¥���������ĸ���ʱ�У�һֱ��2010�������Ե�װ�硣�����к���������ĺ���������������ò����ʹ������Ҳѷɫ���֡�
�Ա߷����˲ü��õ����ʱ��ʱ��Ů���Ǿ�Ϊ��ǿ���ֿ�����
ǽ�Ϲ���һ����(zi)�������쳣���������������ֱʡ�
LONG );
	 set("no_fight", 1);
	set("exits", ([
		"down" : __DIR__"garments",
	]));
	set("objects", ([
		__DIR__"npc/lanlan": 1,
	]));
	setup();
}

