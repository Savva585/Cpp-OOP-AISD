
import matplotlib.pyplot as plt
import networkx as nx
import json

def main():
    try:
        with open('graph_data.json', 'r', encoding='utf-8') as f:
            data = json.load(f)
    except FileNotFoundError:
        print("Error: graph_data.json not found")
        return
    
    G = nx.DiGraph()
    
    for v in data['vertices']:
        G.add_node(v)
    
    for e in data['edges']:
        G.add_edge(e['from'], e['to'], weight=e['weight'])
    
    plt.figure(figsize=(12, 8))
    
    pos = nx.spring_layout(G, seed=42, k=1.5)
    
    nx.draw_networkx_nodes(G, pos, 
                          node_color='lightblue',
                          node_size=800,
                          edgecolors='black',
                          linewidths=2)
    
    nx.draw_networkx_edges(G, pos,
                          edge_color='gray',
                          arrows=True,
                          arrowsize=20,
                          arrowstyle='-|>',
                          width=1.5,
                          connectionstyle='arc3,rad=0.1')
    
    nx.draw_networkx_labels(G, pos, font_size=12, font_weight='bold')
    
    edge_labels = nx.get_edge_attributes(G, 'weight')
    nx.draw_networkx_edge_labels(G, pos, edge_labels=edge_labels, font_size=10)
    
    plt.title('Trade Points Graph', fontsize=14, fontweight='bold')
    plt.axis('off')
    plt.tight_layout()
    
    plt.savefig('graph.png', dpi=150, bbox_inches='tight')
    print("Graph saved to: graph.png")
    
    plt.show()

if __name__ == '__main__':
    main()