// xiaomiao.c ������ 
inherit ROOM; 
void create() 
{ 
	set("short", "������"); 
	set("long", @LONG 
��������ԭ�����书���е�������������Ϊ�ܾ�û�����ɹ��� 
�Ѿ����ò���������ү�Ľ���Ҳֻʣ���˰�أ�����ֻʣ�������� 
�ȣ������Ѿ�ȫ���¹��ˣ���������ƶ������ûؼ�ȥ����ȡů�� 
����ƽ����û�������ģ�ֻ��һЩ���ֺ��еĵ�Ʀ��å֮������� 
�����˼ҡ���������Լ¶����һ��С����
LONG 
	);
	set("exits", ([ 
		"north" : __DIR__"xijie", 
	])); 
	set("item_desc", ([ 
		"��������" : "һ��ֻʣ�����ȵ��ƾɹ������������и����صúܺõ�С����\n"
		ZJOBACTS2"�궴:enter dong\n",
	])); 
	set("objects", ([ 
		 __DIR__"npc/dipi" : 1,
	]));	
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
				me->name() + "����ؤ�����ǹ���һ��������"
					     "�����˽�ȥ��\n", 
				environment(me), me); 
			me->move("/d/gaibang/underwg"); 
			message("vision", 
				me->name() + "�Ӷ������˽�����\n", 
				environment(me), ({me}) ); 
			return 1; 
		} 
		else  
			return notify_fail("��ôС�Ķ�������ý�ȥ��\n"); 
	} 
} 


