
// Room: nanheqiaow.c
inherit ROOM;
void create()
{
	set("short","�Ϻ���");
	set("long",@LONG
�����ǳɶ��������Ϻ��š����Ӻ��ϺӼг��������ǻ��������
��֮�����׸�֮�ء���ˮ���±�͸�������������ţ���������佻�Ϫ
�ˡ�
LONG);
	set("outdoors", "chengdu");
	set("exits",([ /* sizeof() == 1 */
	    "west"  : __DIR__"path1",
	    "east"  : __DIR__"westgate",
	]));
	set("no_clean_up", 0);
	setup();
}

