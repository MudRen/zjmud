// tuwu.c  С����
inherit ROOM; 
void create() 
{ 
	set("short", "С����"); 
	set("long", @LONG 
����һ���û����ݳɵ�С�ݣ����ڴ�ɨ�ĺܸɾ������ܵ�ǽ����
�����˸��ֹ��ӣ�ǥ�ӣ���ɽ����С���ӵȹ��ߣ������ƺ��ǲɲ���
�õĹ��ߡ���������Ļ�������һλ������͵����ˣ��������ź�
�̴�����������һ��С����
LONG 
	);
	set("exits", ([ 
		"north" : __DIR__"xiaoxiang", 
	])); 
	set("item_desc", ([ 
		"��С����" : "һ���ڽ��������صúܺõ�С����\n"
		ZJOBACTS2"�궴:enter dong\n",
	]));
	set("outdoors", "guanwai"); 
	set("no_clean_up", 0);       
	setup(); 
} 
      
void init() 
{ 
	add_action("do_enter", "enter"); 
	add_action("do_enter", "zuan"); 
} 

int do_enter(string arg) 
{ 
	object me; 
	mapping fam; 
       
	me = this_player(); 
	if (! arg || arg == "") return 0; 
	if (arg == "dong") 
	{ 
		if (me->query("family/family_name") == "ؤ��")  
		{ 
			message("vision", 
				me->name() + "����ؤ�����ǹ���һ�������������˽�ȥ��\n", 
				environment(me), me); 
			me->move("/d/gaibang/undergw"); 
			message("vision", 
				me->name() + "�Ӷ������˽�����\n", 
				environment(me), ({me}) ); 
			return 1; 
		} 
		else  
			return notify_fail("��ôС�Ķ�������ý�ȥ��\n"); 
	} 
} 


