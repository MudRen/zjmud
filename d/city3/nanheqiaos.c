
// Room: nanheqiaos.c
inherit ROOM;
void create()
{
	set("short","�Ϻ���");
	set("long",@LONG
�����ǳɶ��������Ϻ��š����Ӻ��ϺӼг���������Ϊ��Ȼ�Ļ�
�Ǻӣ�����������츮֮���Ĵ����׸����򱱾ͽ����ˣ���������һ
��С·��
LONG);
	set("outdoors", "chengdu");
	set("exits",([ /* sizeof() == 1 */
	    "south"  : "/d/xuedao/sroad1",
	    "north"  : __DIR__"southgate",
	]));
	set("no_clean_up", 0);
	setup();
}

