//Room: bank.c
#include <ansi.h>
inherit ROOM;
void create ()
{
	set ("short", "�ĺ�Ǯׯ");
	set ("long", @LONG
���ǳ����ǵ�һ�����ֺ�Ǯׯ���ϰ���ɽ���ˣ����Ǯׯ��������
����������ʱ�Ϳ�ʼ����һֱ�����������Ǯׯ�������ǳ��ã���
����ȫ�����ض����˷ֵꡣ�����е���Ʊͨ��ȫ����Ǯׯ���ſڹ���һ
�����ӡ�
LONG);
	set("item_desc", ([
		"�����ӡ�" : "��Ǯׯ�ṩ���·���\n"
		ZJOBACTS2+ZJMENUF(3,3,8,30)"��Ǯ:cun"ZJSEP"ȡǮ:qu"ZJSEP"����:check\n",
	]) );
	set("exits", 
	([ //sizeof() == 1
		"south" : __DIR__"qixiang4",
	]));
	set("objects", 
	([ //sizeof() == 1
		__DIR__"npc/tiegongji" : 1,
	]));

	set("no_clean_up", 0);
	setup();
}
