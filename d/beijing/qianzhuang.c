inherit ROOM;
void create()
{
	set("short", "����Ǯׯ");
	set("long", @LONG
����Ǯׯ�Ǿ���������һ��Ǯׯ���Ѿ��й��������ʷ�ˣ������൱
�ĺá�Ǯׯ�Ĵ���������һ���߸ߵĹ�̨��Ǯׯ���ϰ����ڹ�̨����������
��Ŀ����̨��ߵ�ǽ�Ϲ���һ�����ӡ�
LONG );
	set("item_desc", ([
		"�����ӡ�" : "��Ǯׯ�ṩ���·���\n"
		ZJOBACTS2+ZJMENUF(3,3,8,30)"��Ǯ:cun"ZJSEP"ȡǮ:qu"ZJSEP"����:check\n",
	]) );
	set("exits", ([
		"south" : __DIR__"di_5",
	]));
	set("no_clean_up", 0);
	set("no_fight", 1);
	set("no_beg", 1);
	set("objects", ([
		__DIR__"npc/tiegongji" : 1
	]));

	setup();
}

