//Room: /d/dali/neitang.c
inherit ROOM;
void create()
{
	set("short","����");
	set("long",@LONG
�������������������á�ʮ�ֿ�������������ǽ�Ϲ���һ��ˮī
�������߸���һ�����ӣ�͸���������Կ����������ɽ��ˮ��
LONG);
	set("objects", ([
	    CLASS_D("duan")+"/duanzc": 1,
	]));
	set("exits",([ /* sizeof() == 1 */
	    "south"  : __DIR__"yongdao2",
	]));
	setup();
}
