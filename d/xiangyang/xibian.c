// Room: /d/xiangyang/xibian.c  Ϫ��
// Date: Jan. 28 2002 by Pound

inherit ROOM;
#include <ansi.h>;

void create()
{
	set("short", "Ϫ��");
	set("long", @LONG
�����Ǵ�·����ʮ�ɴ����﹡����һ���峺��СϪ��xiaoxi��������
�����˴���Բ���������������̣����Ҳ��Щ���ߡ�ֻ���ϱ��м���é��
��һ��Ƭ��������Ļ��ԣ�����ߵ������γ��������Աȡ�
LONG );
	set("outdoors", "xiangyang");
	set("resource/water", 1);
	set("exits", ([
	    "south" : __DIR__"huapu",
	]));
	set("item_desc", ([
	    "xiaoxi" : "����һ��СϪ��Ϫˮ�峺͸�ף�����������Ҩˮ(yao shui)������\n",  
	]));

	setup();
}

int init()
{
	add_action("do_fill", "fill");
    
}

int do_fill(string arg)
{

	object me, ob;
	me = this_player();
	ob = present("shui tong", me);
	
	if (! arg || (arg != "tong" && arg != "shuitong" && arg != "shui tong"))
	    return notify_fail("��Ҫ��ʲô����װˮ��\n");   
	if (! ob) return
	    notify_fail("��û�д�ˮͰ����ôװˮ��\n");
	if (me->is_busy())
	    return notify_fail("����æ���أ�\n");
/*      if (ob->query("water_level") > 4)
	    return notify_fail("Ͱ���Ѿ�ʢ����ˮ�ˡ�\n");
*/
	if (random(20) == 1)
	{ 
	    message_vision(HIR "$N" HIR "��С��һ����������һ��,��Ͱ����СϪ�ﱻ�����ˡ�"NOR"\n", me);
	    destruct(ob);
	    return 1;
	}
	message_vision("$N����������Ͱ�Ž��峺��СϪ��װ����ˮ��\n", me);
	ob->set("water_level", 5);
	ob->set("long", HIY "����һ�����Ƶ�ˮͰ��" NOR + HIC "����װ����ˮ��"NOR"\n");
	me->start_busy(3 + random(2));
	me->receive_damage("jing", (28 + random(3)));
	return 1;
}