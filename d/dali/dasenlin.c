//Room: /d/dali/dasenlin.c
inherit ROOM;
void create()
{
	set("short","��ɭ��");
	set("long",@LONG
��ȥ��������ɽ���ʹ�ɭ�֣������Ѿ���ľï���˼�
�����ˣ������Ǵ�����ԭ�Ĺٵ���·��
LONG);
	set("outdoors", "dali");
	set("exits",([ /* sizeof() == 1 */
	    "south"   : __DIR__"dianchi",
	    "north"   : __DIR__"heisenlin",
	]));
	set("no_clean_up", 0);
	setup();
}

