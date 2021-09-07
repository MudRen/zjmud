// mapd.c

#pragma optimize
#pragma save_binary

#include <ansi.h>

// ��ʶ��Ӧ�ĵ���
mapping map_short = ([
	"xiyu"      : "����",
	"xingxiu"   : "���޺�",
	"guanwai"   : "����",
	"city"      : "����",
	"fuzhou"    : "����",
	"ruzhou"    : "����",
	"xiangyang" : "����",
	"suzhou"    : "����",
	"item"      : "������",
	"hangzhou"  : "����",
	"quanzhou"  : "Ȫ��",
	"lingzhou"  : "����",
	"city3"     : "�ɶ�",
	"jiaxing"   : "����",
	"nanyang"   : "����",
	"foshan"    : "��ɽ",
	"dali"      : "����",
	"changan"   : "����",
	"wugong"    : "�书",
	"hengyang"  : "����",
	"beijing"   : "����",
	"shaolin"   : "����",
	"wudang"    : "�䵱",
	"emei"      : "����",
	"qingcheng" : "���",
	"mingjiao"  : "����ɽ",
	"quanzhen"  : "����ɽ(�书��)",
	"henshan"   : "��ɽ",
	"taishan"   : "̩ɽ",
	"huashan"   : "��ɽ",
	"hengshan"  : "��ɽ",
	"songshan"  : "��ɽ",
	"huanghe"   : "�ƺ�",
	"lingjiu"   : "��ɽ",
	"gumu"      : "��Ĺ",
	"meizhuang" : "÷ׯ",
	"tianlongsi": "������",
	"xueshan"   : "ѩɽ",
	"taohua"    : "�һ���",
	"baituo"    : "����ɽ",
	"shenlong"  : "������",
	"yanziwu"   : "������",
	"village"   : "��ɽ��",
	"xiakedao"  : "���͵�",
	"xiaoyao"   : "��ң��",
	"wanjiegu"  : "��ٹ�",
	"xuedao"    : "��ѩɽ",
	"guiyun"    : "����ׯ",
	"heimuya"   : "��ľ��",
	"motianya"  : "Ħ����",
	"nanhai"    : "�Ϻ�֮��",
]);

// ��ʶ��Ӧ�ĵ�ͼ�����ļ�(ȫ����HELP_DIR��)
mapping map_to = ([
	"xiyu"      : "map_xy",
	"xingxiu"   : "map_xxh",
	"guanwai"   : "map_gw",
	"city"      : "map_yz",
	"fuzhou"    : "map_fz",
	"xiangyang" : "map_xi",
	"suzhou"    : "map_sz",
	"hangzhou"  : "map_hz",
	"quanzhou"  : "map_qz",
	"lingzhou"  : "map_lz",
	"chengdu"   : "map_cd",
	"jiaxing"   : "map_jx",
	"nanyang"   : "map_ny",
	"foshan"    : "map_fs",
	"dali"      : ({ "map_dl", "map_dalie", "map_daliw", "map_dalis", "map_dalin" }),
	"changan"   : "map_ca",
	"wugong"    : "map_wg",
	"hengyang"  : "map_hy",
	"beijing"   : ({ "map_bjw", "map_bje" }),
	"shaolin"   : "map_sl",
	"wudang"    : "map_wd",
	"emei"      : "map_em",
	"qingcheng" : "map_qc",
	"mingjiao"  : "map_kl",
	"quanzhen"  : ({ "map_zn", "map_cyg" }),
	"henshan"   : "map_ss",
	"taishan"   : "map_es",
	"huashan"   : "map_ws",
	"hengshan"  : "map_ns",
	"songshan"  : "map_cs",
	"huanghe"   : "map_hh",
	"lingjiu"   : "map_ljf",
	"gumu"      : "map_gm",
	"meizhuang" : "map_mz",
	"tianlongsi": "map_tls",
	"xueshan"   : "map_xss",
	"taohua"    : "map_thd",
	"baituo"    : "map_bts",
	"shenlong"  : "map_sld",
	"yanziwu"   : "map_yzw",
	"village"   : "map_hsc",
	"xiakedao"  : "map_xkd",
	"xiaoyao"   : "map_xyl",
	"wanjiegu"  : "map_wjg",
	"xuedao"    : "map_xdm",
	"guiyun"    : "map_gyz",
	"heimuya"   : "map_hmy",
	"motianya"  : "map_mty",
	"nanhai"    : "map_nh",
]);

// ���ؽ�ͨ�����
mapping map_trans = ([
	"beijing"   : ([ "name" : "����",     "room" : "/d/beijing/majiu", ]),
	"yangzhou"  : ([ "name" : "����",     "room" : "/d/city/majiu", ]),
	"dali"      : ([ "name" : "����",     "room" : "/d/dali/majiu", ]),
	"foshan"    : ([ "name" : "��ɽ",     "room" : "/d/foshan/majiu", ]),
	"fuzhou"    : ([ "name" : "����",     "room" : "/d/fuzhou/majiu", ]),
	"guanwai"   : ([ "name" : "����",     "room" : "/d/guanwai/majiu", ]),
	"hangzhou"  : ([ "name" : "����",     "room" : "/d/hangzhou/majiu", ]),
	"lingzhou"  : ([ "name" : "����",     "room" : "/d/lingzhou/majiu", ]),
	"yongdeng"  : ([ "name" : "����",     "room" : "/d/huanghe/majiu", ]),
	"suzhou"    : ([ "name" : "����",     "room" : "/d/suzhou/majiu", ]),
	"xiangyang" : ([ "name" : "����",     "room" : "/d/xiangyang/majiu", ]),
	"yili"      : ([ "name" : "����",     "room" : "/d/xingxiu/majiu", ]),
	"chengdu"   : ([ "name" : "�ɶ�",     "room" : "/d/city3/majiu", ]),
	"emei"      : ([ "name" : "����ɽ",   "room" : "/d/emei/majiu1", ]),
	"emei2"     : ([ "name" : "���Ұ�ɽ", "room" : "/d/emei/majiu2", ]),
	"quanzhou"  : ([ "name" : "Ȫ��",     "room" : "/d/quanzhou/majiu1", ]),
	"jiaxing"   : ([ "name" : "����",     "room" : "/d/quanzhou/majiu2", ]),
	"nanyang"   : ([ "name" : "����",     "room" : "/d/shaolin/majiu1", ]),
	"changan"   : ([ "name" : "����",     "room" : "/d/changan/majiu", ]),
	"wugong"    : ([ "name" : "�书��",   "room" : "/d/quanzhen/majiu", ]),
	"hengyang"  : ([ "name" : "����",     "room" : "/d/henshan/majiu", ]),
]);

// ��ͨ����
mixed connect_info = ({
	({ "beijing", "guanwai",	300, }),
	({ "beijing", "lingzhou",       300, }),
	({ "beijing", "changan",	200, }),
	({ "beijing", "xiangyang",      200, }),
	({ "beijing", "nanyang",	150, }),
	({ "beijing", "yangzhou",       200, }),
	({ "lingzhou", "yili",	  250, }),
	({ "lingzhou", "yongdeng",      100, }),
	({ "lingzhou", "changan",       200, }),
	({ "changan", "yili",	   250, }),
	({ "changan", "wugong",	 50,  }),
	({ "changan", "xiangyang",      200, }),
	({ "changan", "nanyang",	200, }),
	({ "changan", "chengdu",	250, }),
	({ "yangzhou", "changan",       200, }),
	({ "yangzhou", "nanyang",       100, }),
	({ "yangzhou", "xiangyang",     150, }),
	({ "yangzhou", "hengyang",      250, }),
	({ "yangzhou", "suzhou",	80,  }),
	({ "yangzhou", "hangzhou",      120, }),
	({ "yangzhou", "jiaxing",       150, }),
	({ "xiangyang", "chengdu",      200, }),
	({ "xiangyang", "dali",	 400, }),
	({ "xiangyang", "hengyang",     200, }),
	({ "chengdu", "emei",	   150, }),
	({ "chengdu", "dali",	   300, }),
	({ "emei",  "emei2",	    20,  }),
	({ "hengyang", "foshan",	150, }),
	({ "suzhou", "hangzhou",	80,  }),
	({ "suzhou", "jiaxing",	 120, }),
	({ "suzhou", "quanzhou",	150, }),
	({ "hangzhou", "jiaxing",       50,  }),
	({ "hangzhou", "quanzhou",      150, }),
	({ "hangzhou", "fuzhou",	140, }),
	({ "jiaxing", "fuzhou",	 130, }),
	({ "fuzhou", "quanzhou",	30,  }),
});

// �鿴ĳ���ص��Ƿ�MAPD��֪��
public int been_known(string outdoors)
{
	return stringp(map_short[outdoors]);
}

// ���ĳ������ص����������
public string query_map_short(string outdoors)
{
	string str;

	if (stringp(str = map_short[outdoors]))
		return str;

	return "����ص�["+outdoors+"]";
}

// ������л���ص�ļ���
public string *query_all_map_zone()
{
	return keys(map_short);
}

// ���ĳ������ص�ĵ�ͼ
public string query_maps(string outdoors)
{
	mixed maps;
	string file;
	string map_result;

	if (undefinedp(maps = map_to[outdoors]))
		return "δ����ϸ��ͼ��\n";

	if (stringp(maps))
	{
		file = HELP_DIR + maps;
		map_result = read_file(file);
		if (! stringp(map_result))
			map_result = "�޷���ȡ��ͼ" + file + "��\n";
		map_result = color_filter(map_result);
		return map_result;
	}

	if (arrayp(maps))
	{
		map_result = "";
		foreach (file in maps)
		{
			if (file_size(HELP_DIR + file) > 0)
				map_result += read_file(HELP_DIR + file);
			else
				map_result += "�޷���ȡ��ͼ" + file + "��\n";
		}
		map_result = color_filter(map_result);
		return map_result;
	}

	error("δ֪����\n");
}

// ��õ�ͼ��ĳһ�еĵ�x��ʼ��n���ַ������е�ͼ����@��ͷ����
// ���������ַ�һ����Ϊ��ռ�ط�������"@B123@E"����ڶ����ַ�
// ��'2'��������B�����nΪ-1���򷵻�һֱ��ĩβ�������ַ�
//
// �����������⣬�б�Ҫ����һ�������� ��ʶ�Ƿ�ȡ����ɫ������
// ���ڳ���ļ����൱С�����Թ��Ҳ��ơ�
string get_map_line(string line, int x, int n)
{
	string rs;

	rs = "";
	if (n == 0)
		return rs;

	// �ҵ���Ӧ��λ��
	while (x)
	{
		if (strlen(line) == 0)
			// �ַ������Ȳ���
			return rs;

		if (line[0] == '@')
		{
			if (strlen(line) >= 2)
				// ȥ��@�ͺ������ַ�
				line = line[2..<1];
			else
				// ���Ȳ��������ؿ��ַ���
				return rs;
		} else
		{
			// �ַ���ȥ����һ���ַ����൱�������ƶ�
			x--;
			line = line[1..<1];
		}
	}

	// ��ȡn���ַ�
	// Ϊʲô������do-while������ֱ����while��������ԭ��
	// �ġ�
	rs = "";
	for (;;)
	{
		if (strlen(line) == 0)
			// �Ѿ����ַ���ȡ
			return rs;

		if (line[0] == '@')
		{
			if (strlen(line) >= 2)
			{
				rs += line[0..1];
				line = line[2..<1];
			} else
			{
				rs += line;
				return rs;
			}
		} else
		{
			if (n == 0) break; // ������ȡ
			n--;
			rs += line[0..0];
			line = line[1..<1];
			continue;
		}
	}
	return rs;
}

// Ϊ�ص�����ɫ�����ֱ���Ϊ����
// ��ǵ�ʱ��һ����ɨ�裬ɨ���ͬʱ���ǣ����������Ϊ@B��
// @E�����ɨ��ɹ��Ͱ�@B��@E�滻��Ϊ@R��@N�������ȥ����Щ
// ��ʱ��ǡ�
// ��󽫽����еı���滻����ɫ��@R->WHT @N->NOR
public string mark_map(string map, string name)
{
	string *lines;
	string temp;
	string rs;
	int i;
	int x, y, xd;	   // �Ƚϵĵ�ͼλ��
	int n;

	// ȥ����ͼ����ɫ����������׼ȷ���жϾ��Ե�����
	map = filter_color(map);

	// ����ͼ�ֳ���
	lines = explode(map, "\n");
	for (i = 0; i < sizeof(lines); i++)
	{
		if (strsrch(lines[i], name[0..1]) == -1)
			// ���в��������Ƶĵ�һ�����֣�������������һ��
			continue;

		x = 0;
		temp = replace_string(lines[i], "@R", "");
		temp = replace_string(temp, "@N", "");
		while (x < strlen(temp) - 1)
		{
			xd = strsrch(temp[x..<1], name[0..1]);
			if (xd == -1)
				// ���к���û�����Ƶĵ�һ�����֣�������һ��
				break;

			// ����ƥ�����˵�һ�����֣��ȽϺ����ĺ��֣�
			// ���Ⱥ���Ƚϣ���˲����ƶ�xd���������ɨ
			// �費������������Ƚϣ��仯y��
			x += xd;
			y = i;
			xd = 2;
			rs = get_map_line(lines[y], 0, x);
			rs += "@B";
			rs += get_map_line(lines[y], x, 2);
			for (n = 2; n < strlen(name); n += 2, xd += 2)
			{
				// ���Ⱥ���Ƚ�
				if (x + xd + 2 <= strlen(lines[y]) &&
				    get_map_line(lines[y], x + xd, 2) == name[n..n + 1])
				{
					// ����Ƚϵ��ˣ���������Ƚ�
					rs += name[n..n + 1];
					continue;
				}

				// ����Ƚ�ʧ���ˣ�����ԭ���룬����Ƚ�
				rs += "@E" + get_map_line(lines[y], x + xd, -1);
				xd = 0;
				y++;
				if (y < sizeof(lines) &&
				    x + 2 <= strlen(lines[y]) &&
				    get_map_line(lines[y], x, 2) == name[n..n + 1])
				{
					// ����Ƚϵ��ˣ���������Ƚ�
					lines[y - 1] = rs;
					rs = get_map_line(lines[y], 0, x);
					rs += "@B";
					rs += name[n..n + 1];
					continue;
				}

				// �Ƚ�ʧ�ܣ�����(x, i)���λ��
				y--;
				while (y >= i)
				{
					// �ָ�ԭ�ȵĵ�ͼ��ȥ�����
					lines[y] = replace_string(lines[y], "@B", "");
					lines[y] = replace_string(lines[y], "@E", "");
					y--;
				}
				break;
			}

			if (n >= strlen(name))
			{
				// ƥ��ɹ�
				rs += "@E" + get_map_line(lines[y], x + xd, -1);
				lines[y] = rs;
				while (y >= i)
				{
					// ���������Ϊ�������
					lines[y] = replace_string(lines[y], "@B", "@R");
					lines[y] = replace_string(lines[y], "@E", "@N");
					y--;
				}
			}

			// �ƶ�x������ƥ��
			x++;
		}
		// ɨ�����һ�У�����ɨ����һ��
	}
	// �������

	return implode(lines, "\n") + "\n";
}

// �������ĳ���ص�ĵ�ͼ����ǵ�ǰ���ڵ�λ��
public string marked_map(object env)
{
	mixed maps;
	string file;
	string outdoors;
	string map_result;
	int result_ok;

	if (! objectp(env))
		return "�����޷���õ�ͼ��\n";

	if (! stringp(outdoors = env->query("outdoors")))
		return "����������쿴�����ľ���λ�á�\n";

	if (undefinedp(maps = map_to[outdoors]))
		return "δ����ϸ��ͼ��\n";

	if (stringp(maps))
	{
		file = HELP_DIR + maps;
		map_result = read_file(file);
		if (! stringp(map_result))
			map_result = "�޷���ȡ��ͼ" + file + "��\n";
		map_result = color_filter(map_result);
		map_result = mark_map(map_result, env->short());
	} else
	if (arrayp(maps))
	{
		map_result = "";
		result_ok = 0;
		foreach (file in maps)
		{
			if (file_size(HELP_DIR + file) > 0)
				map_result = read_file(HELP_DIR + file);
			else
			{
				map_result = "�޷���ȡ��ͼ" + file + "��\n";
				result_ok = 1;
				break;
			}

			map_result = color_filter(map_result);
			map_result = mark_map(map_result, env->short());
			if (strsrch(map_result, "@R") != -1)
			{
				result_ok = 1;
				break;
			}
		}
		// ���еĵ�ͼ��û�б仯��ȡ��һ��
		if (! result_ok)
		{
			map_result = read_file(HELP_DIR + maps[0]);
			map_result = color_filter(map_result);
		}
	} else
		error("δ֪����\n");

	map_result = replace_string(map_result, "@R", BBLU+HIY);
	map_result = replace_string(map_result, "@N", NOR);
	return map_result;
}

// ��Ҽ�¼����
public int record_rumor(mixed obs, string topic, mixed event_ob)
{
	object ob;
	string title;
	int n;

	if (objectp(obs)) obs = ({ obs }); else
	if (! arrayp(obs)) return 0;

	if (! stringp(title = event_ob->query_detail(topic)))
		return 0;

	if (stringp(event_ob)) event_ob = base_name(find_object(event_ob)); else
			       event_ob = base_name(event_ob);
	n = 0;
	foreach (ob in obs)
	{
		if (! playerp(ob) || ! ob->query("out_family")) continue;
		if (ob->query("rumor/" + topic)) continue;
		ob->set("rumor/" + topic, event_ob);
		message("vision", "���ͳ���ͼ�ᣬ��������棬д�����йء�" +
				  topic + "���ļ�¼��\n", ob);
		n++;
	}

	return n;
}

// ���ĳ����ͨ�ص����Ϣ
public varargs mixed query_trans_info(string to)
{
	if (! stringp(to))
		return map_trans;

	return map_trans[to];
}

// ��ý�ͨ������Ϣ
public mapping query_connect_info()
{
	return connect_info;
}
